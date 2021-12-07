class Main {
    c : Int <- 10;
    d : Int <- 10;
    b : Float <- 20.0;
    main() : Int {
        (new SelfType).getc()
    };

    getc() : Int {
        c
    };
};

class Main4 inherits Main2 {
    c : Float <- 20.2;
    d : Int <- 5;
    hello(i : Int, i2 : Int, b : Bool) : Int {
        if b then
            while d.oplt(10) loop {
                d <- d.opadd(1);
                i <- i.opadd(1);
            }
            pool
        else
            i.opadd(i2)
        fi
    };

    hello2(i : Int) : Int {
        let count : Int <- 1 in
            while not count.opgt(10) loop {
                count <- count + 2;
                i <- i + 1;
            } pool
    };

    hello3(i : Int, i2 : Int) : Int {
        if isvoid i then
            i2
        else
            i
        fi
    };
};

class Main2 inherits Main {
    c : Int <- 3;
};