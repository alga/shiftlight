// Quick and dirty enclosure for the arduino shift light

module board() {
	cube([49, 29, 1.6]);
	for(i=[0:4]) {
	    translate([10.2 + i*7.62, 0, 2]) rotate([90, 0, 0]) hull() {
			cylinder(r=2.6, h=8.7-2.5, $fn=20);
			translate([0,0,8.7-2.6]) sphere(2.6, $fn=20);
		}
	}
	translate([1, 7, 0]) cube([42, 18, 16]);
}


module box() {
	difference() {
		cube([51, 36, 22]);
		translate([2, 2, 1]) cube([47, 36, 20]);
		translate([1, 6, 4]) union() {
			board();
			translate([0, -2, 0]) cube([49, 40, 1.6]);
		}
	}
}

module lid() {
    translate([0, 37, -10]) rotate([180, 0, 0]) 
    difference() {
	    translate([0.01, 35, 0.01]) cube([50.98, 2, 21.98]);
        box();
        translate([5.5, 38, 1]) rotate([90, 0, 0]) cylinder(r=3, h=10, $fn=20);
    }
}

rotate([90, 0, 0]) union() {
	box(); 
	lid();
	%translate([1, 6, 4]) board();
}
