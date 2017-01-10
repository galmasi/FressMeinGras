module UltraSoundBase() {
  // box dimensions for servo

  w=23; 
  d=13;
  h=15;

  // box dimensions for Arduino Pro Mini

  w2=35;
  d2=20;
  
  difference() {
    union() {
      cylinder($fn=40,r=d*1.2,h=h+2);

      translate([d*2,0,h/2+1])
      cube([w+8,d+8,h+2],center=true);

      translate([-d*2.3,0,h/2+1])
      cube([w2+4,d2+4,h+2],center=true);

    }
    union() {
      translate([0,0,-1])
      cylinder($fn=40,r=4,h=h+4);

      translate([d*2,0,h/2+3])
      cube([w,d,h],center=true);

      translate([d*3,0,h/4+3])
      cube([w,d,h/2],center=true);

      translate([-d*2.3,0,h/2+3])
      cube([w2,d2,h],center=true);
    }
  }
}

UltraSoundBase();
