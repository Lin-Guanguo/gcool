class Main {
    main() : Int {
        let s1 : Shape <- new Rect, s2 : Shape <- new Circle in {
            (new Std).printFloat(s1.area());
            (new Std).printEndLine();
            (new Std).printFloat(s2.area());
            (new Std).printEndLine();
        }
    };
};

class Shape {
    area() : Float {
        null
    };
};

class Rect inherits Shape {
    long : Float <- 5.0;
    short : Float <- 2.3;
    area() : Float {
        long * short
    };
};

class Circle inherits Shape {
    r : Float <- 5.0;
    area() : Float {
        r * r * 3.14
    };
};


