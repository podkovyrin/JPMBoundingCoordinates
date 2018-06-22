//
//  JPMBoundingCoordinates.m
//
//  Created by Andrew Podkovyrin on 01/05/14.
//  Copyright (c) 2014 Andrew Podkovyrin. All rights reserved.
//
//  Original author: Jan Philip Matuschek
//  http://JanMatuschek.de/LatitudeLongitudeBoundingCoordinates
//

#import "JPMBoundingCoordinates.h"

static double const kDegToRad = (M_PI / 180.f);
static double const kRadToDeg = (180.f / M_PI);

static double const kEARTH_RADIUS_IN_METERS = 6372797.560856f;

static CGFloat const kMIN_LAT = -M_PI / 2; // -90
static CGFloat const kMAX_LAT = M_PI / 2;  // 90
static CGFloat const kMIN_LNG = -M_PI;     // -180
static CGFloat const kMAX_LNG = M_PI;      // 180

///

JPMSphericalTrapezium const kJPMSphericalTrapeziumInvalid = {{-180, -180}, {-180, -180}};

///

BOOL JPMSphericalTrapeziumIsValid(JPMSphericalTrapezium sphericalTrapezium) {
    CLLocationDegrees invalidDegree = kJPMSphericalTrapeziumInvalid.northEast.latitude;
    return (sphericalTrapezium.southWest.latitude != invalidDegree &&
            sphericalTrapezium.southWest.longitude != invalidDegree &&
            sphericalTrapezium.northEast.latitude != invalidDegree &&
            sphericalTrapezium.northEast.longitude != invalidDegree);
}

///

@interface JPMBoundingCoordinates () {
    double latitudeRad;
    double longitudeRad;
}

@end


@implementation JPMBoundingCoordinates

+ (JPMSphericalTrapezium)boundsFromCoordinate:(CLLocationCoordinate2D)centerCoordinate distance:(CLLocationDistance)distance {
    JPMBoundingCoordinates *boundingCoordinates = [self fromCoordinate:centerCoordinate];
    if (boundingCoordinates) {
        return [boundingCoordinates boundsWithDistance:distance];
    }
    return kJPMSphericalTrapeziumInvalid;
}

+ (instancetype)fromCoordinate:(CLLocationCoordinate2D)centerCoordinate {
    return [[self alloc] initWithCenterCoordinate:centerCoordinate];
}

- (instancetype)initWithCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate {
    if (!CLLocationCoordinate2DIsValid(centerCoordinate)) {
        return nil;
    }
    
    self = [super init];
    if (self) {
        latitudeRad = centerCoordinate.latitude * kDegToRad;
        longitudeRad = centerCoordinate.longitude * kDegToRad;
    }
    return self;
}

#pragma mark -

- (JPMSphericalTrapezium)boundsWithDistance:(CLLocationDistance)distance {
    return [self boundsWithDistance:distance radius:kEARTH_RADIUS_IN_METERS];
}

- (JPMSphericalTrapezium)boundsWithDistance:(CLLocationDistance)distance radius:(double)radius {
    if (radius < 0.f || distance < 0.f) {
        return kJPMSphericalTrapeziumInvalid;
    }
    
    // angular distance in radians on a great circle
    double distanceRad = distance / radius;
    
    double minLat = latitudeRad - distanceRad;
    double maxLat = latitudeRad + distanceRad;
    
    double minLng, maxLng;
    if (minLat > kMIN_LAT && maxLat < kMAX_LAT) {
        double deltaLon = asin(sin(distanceRad) / cos(latitudeRad));
        
        minLng = longitudeRad - deltaLon;
        if (minLng < kMIN_LNG) {
            minLng += 2.f * M_PI;
        }
        
        maxLng = longitudeRad + deltaLon;
        if (maxLng > kMAX_LNG) {
            maxLng -= 2.f * M_PI;
        }
    } else {
        // a pole is within the distance
        minLat = MAX(minLat, kMIN_LAT);
        maxLat = MIN(maxLat, kMAX_LAT);
        minLng = kMIN_LNG;
        maxLng = kMAX_LNG;
    }
    
    return JPMSphericalTrapeziumMake(CLLocationCoordinate2DMake(minLat * kRadToDeg, minLng * kRadToDeg),
                                     CLLocationCoordinate2DMake(maxLat * kRadToDeg, maxLng * kRadToDeg));
}

@end
