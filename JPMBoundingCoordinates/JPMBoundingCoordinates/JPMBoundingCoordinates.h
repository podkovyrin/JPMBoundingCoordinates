//
//  JPMBoundingCoordinates.h
//
//  Created by Andrew Podkovyrin on 01/05/14.
//  Copyright (c) 2014 Andrew Podkovyrin. All rights reserved.
//
//  Original author: Jan Philip Matuschek
//  http://JanMatuschek.de/LatitudeLongitudeBoundingCoordinates
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


/**
 *  Rectangle, specified by two corner coordinates
 *
 *  -   NE
 *
 *  SW   -
 */
typedef struct {
    CLLocationCoordinate2D southWest; // min
    CLLocationCoordinate2D northEast; // max
} JPMSphericalTrapezium;

/**
 *  Returns a coordinate bounds with the specified min and max coordinates.
 *
 *  @param southWest min coordinate
 *  @param northEast max coordiate
 *
 *  @return A coordinate bounds with the specified min and max coordinates.
 */
static inline JPMSphericalTrapezium JPMSphericalTrapeziumMake(CLLocationCoordinate2D southWest, CLLocationCoordinate2D northEast) {
    JPMSphericalTrapezium bounds;
    bounds.southWest = southWest;
    bounds.northEast = northEast;
    return bounds;
}


/**
 *  Used to specify an invalid JPMSphericalTrapezium
 */
extern JPMSphericalTrapezium const kJPMSphericalTrapeziumInvalid;


/**
 *  Class for calculating coordinate bounds with given distance and optional radius.
 */
@interface JPMBoundingCoordinates : NSObject

/**
 *  Get coordinate bounds for given distance. Used Earth radius for calculation.
 *  In case of incorrect `centerCoordinate` or `distance` returns `kJPMSphericalTrapeziumInvalid`.
 *
 *  A `distance` is considered invalid if it less then zero.
 *  A `centerCoordinate` is considered invalid if `CLLocationCoordinate2DIsValid` returns `NO`.
 *
 *  @param centerCoordinate A coordinate containing latitude and longitude values.
 *  @param distance         A distance in meters from the `centerCoordinate`.
 *
 *  @return `JPMSphericalTrapezium` or `kJPMSphericalTrapeziumInvalid`
 */
+ (JPMSphericalTrapezium)boundsFromCoordinate:(CLLocationCoordinate2D)centerCoordinate distance:(CLLocationDistance)distance;

/**
 *  Get instance of `JPMBoundingCoordinates`.
 *
 *  May return `nil` if `CLLocationCoordinate2DIsValid` returns `NO`.
 *
 *  @param centerCoordinate A coordinate containing latitude and longitude values.
 *
 *  @return `JPMBoundingCoordinates` or `nil`
 */
+ (instancetype)fromCoordinate:(CLLocationCoordinate2D)centerCoordinate;

/**
 *  Get instance of `JPMBoundingCoordinates`.
 *
 *  May return `nil` if `CLLocationCoordinate2DIsValid` returns `NO`.
 *
 *  @param centerCoordinate A coordinate containing latitude and longitude values.
 *
 *  @return `JPMBoundingCoordinates` or `nil`
 */
- (instancetype)initWithCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate;

/**
 *  Get coordinate bounds for given distance. Used Earth radius for calculation.
 *  In case of incorrect `distance` returns `kJPMSphericalTrapeziumInvalid`.
 *
 *  A `distance` is considered invalid if it less then zero.
 *
 *  @param distance A distance in meters.
 *
 *  @return `JPMSphericalTrapezium` or `kJPMSphericalTrapeziumInvalid`
 */
- (JPMSphericalTrapezium)boundsWithDistance:(CLLocationDistance)distance;

/**
 *  Get coordinate bounds for given distance. Used Earth radius for calculation.
 *  In case of incorrect `radius` or `distance` returns `kJPMSphericalTrapeziumInvalid`.
 *
 *  A `distance` is considered invalid if it less then zero.
 *  A `radius` is considered invalid if it less then zero.
 *
 *  @param distance A distance in meters from the `centerCoordinate`.
 *  @param radius   A radius in meters.
 *
 *  @return `JPMSphericalTrapezium` or `kJPMSphericalTrapeziumInvalid`
 */
- (JPMSphericalTrapezium)boundsWithDistance:(CLLocationDistance)distance radius:(double)radius;

@end
