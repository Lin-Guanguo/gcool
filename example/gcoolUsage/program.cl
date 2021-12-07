class Main {
    rect : Rect <- (new Rect).set(5.0, 5.0);
    circle : Circle <- (new Circle).set(5.0);
    main() : Int {
        let s1 : Shape, s2 : Shape in {
            s1 <- rect;
            s2 <- circle;
            (new Std).printFloat(s1.area());
            (new Std).printEndLine();
            (new Std).printFloat(s2.area());
            (new Std).printEndLine();
            (new Std).printFloat(s1.area() + s2.area());
            (new Std).printEndLine();
            (new Std).printEndLine();

            (new Std).printInt(fact(5));
            (new Std).printEndLine();
            (new Std).printInt(fact2(5));
            (new Std).printEndLine();
        }
    };

    fact(i : Int) : Int {
        if i = 0 then
            1
        else 
            i * fact(i-1)
        fi
    };

    fact2(i : Int) : Int {
        if i = 0 then
            1
        else 
            let res : Int <- 1 in
                while not i = 0 loop{
                    res <- res * i;
                    i <- i - 1;
                    res;
                }pool
        fi
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
    set(l : Float, s : Float) : SelfType {{
        long <- l;
        short <- s;
        self;
    }};
};

class Circle inherits Shape {
    r : Float <- 5.0;
    area() : Float {
        r * r * 3.14
    };
    set(r_ : Float) : SelfType {{
        r <- r_;
        self;
    }};
};


