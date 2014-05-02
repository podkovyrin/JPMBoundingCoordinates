JPMBoundingCoordinates
==========

Finding Points Within a Distance of a Latitude/Longitude Using Bounding Coordinates.

About:
----------

Computes the bounding coordinates of all points on the surface of a sphere that have a great circle distance to the given point.
This code was ported to Objective-C directly from http://janmatuschek.de/LatitudeLongitudeBoundingCoordinates, and is owned by Jan Philip Matuschek.


## Usage
 - **[CocoaPods](http://cocoapods.org):**
```
pod 'JPMBoundingCoordinates'
```
 - **Manual:**
Copy `JPMBoundingCoordinates/JPMBoundingCoordinates` folder anywhere to your project and add it to XCode.


##Sample

```obj-c
#import "JPMBoundingCoordinates.h"

JPMSphericalTrapezium bounds = [JPMBoundingCoordinates boundsFromCoordinate:CLLocationCoordinate2DMake(55.750056, 37.615707) distance:1000];

// or
JPMBoundingCoordinates *boundingCoordinates = [JPMBoundingCoordinates fromCoordinate:CLLocationCoordinate2DMake(55.750056, 37.615707)];
JPMSphericalTrapezium bounds1 = [boundingCoordinates boundsWithDistance:100];
JPMSphericalTrapezium bounds2 = [boundingCoordinates boundsWithDistance:200];
```

`JPMSphericalTrapezium` is a C-struct with `southWest` (min) and `northEast` (max) locations.


## Compatibility
iOS 4.3 or later.


## License

JPMBoundingCoordinates is available under the MIT license.
All code written by Jan Philip Matuschek and ported by Andrew Podkovyrin (which is all of this class) is owned by Jan Philip Matuschek.

Copyright © 2014 Andrew Podkovyrin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
