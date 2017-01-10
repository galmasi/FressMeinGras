module UltraSoundRadome() {
  radarheight=20;
  radarwidth=45;

  basewidth=4;
  wallwidth=3;

  difference() {
    union() {
      cylinder($fn=40,r=30,h=basewidth);
 
      translate([0,10+wallwidth/2,radarheight/2+basewidth])
      cube([radarwidth,3,radarheight],center=true);

      translate([radarwidth/2+wallwidth/2-1,wallwidth,radarheight/2+basewidth])
      cube([3,20,radarheight],center=true);

      translate([-radarwidth/2-wallwidth/2+1,wallwidth,radarheight/2+basewidth])
      cube([3,20,radarheight],center=true);
    }
    union() {

      translate([0,7,radarheight/2+basewidth])
      cube([radarwidth+2,4,radarheight+2],center=true);

      cylinder($fn=30,r=3,h=10,center=true);

      translate([-10.75,0,0])
      cylinder($fn=20,r=1,h=10,center=true);

      translate([10.75,0,0])
      cylinder($fn=20,r=1,h=10,center=true);
  }
 }
}

UltraSoundRadome();
