package mandelbrot.complex;


public class Complex implements Field<Complex> {

    private double re, im;

    /**
     * Konstruktor domyślny, który nie przyjmuje żadnych argumentów
     */
    public Complex() {
        this.re = 0;
        this.im = 0;
    }

    /**
     * Konstruktor przypisujący zmiennej re wartość x
     * @param x Liczba zmiennoprzecinkowa podwójnej precyzji
     */
    public Complex(double x) {
        this.re = x;
        this.im = 0;
    }
    /**
     * Konstruktor przypisujący zmiennej re wartość x oraz zmiennej im wartość y
     * @param x Liczba zmiennoprzecinkowa podwójnej precyzji
     * @param y Liczba zmiennoprzecinkowa podwójnej precyzji
     */
    public Complex(double x, double y) {
        this.re = x;
        this.im = y;
    }
    /**
     * Konstruktor przypisujący zmiennej re wartość re obiektu x oraz zmiennej im wartość im obiektu x
     * @param x Obiekt klasy Complex
     */
    public Complex(Complex x) {
        this.re = x.re;
        this.im = x.im;
    }
    /**
     * Konstruktor przyjmujący obiekt klasy String jako argument, konwertujący go na obiekt typu Complex
     * oraz przypisujący zmiennej re wartość re obiektu oraz zmiennej im wartość im obiektu
     * @param object Obiekt klasy String
     */
    public Complex(String object) throws NotAComplexNumberException {
        Complex newComplex = Complex.valueOf(object);

        this.re = newComplex.re();
        this.im = newComplex.im();
    }

    /**
     * Metoda implementująca operację dodawania w liczbach zespolonych
     * @param x Obiekt klasy Complex
     * @return Wynik dodawania obiektu wywołującego metodę przez obiekt x
     */
    @Override
    public Complex add(Complex x) {  // Dodawanie
        this.re += x.re;
        this.im += x.im;

        return this;
    }

    /**
     * Metoda implementująca operację odejmowania w liczbach zespolonych
     * @param x Obiekt klasy Complex
     * @return Wynik odejmowania obiektu wywołującego metodę przez obiekt x
     */
    @Override
    public Complex sub(Complex x) {  // Odejmowanie
        this.re -= x.re;
        this.im -= x.im;

        return this;
    }

    /**
     * Metoda implementująca operację mnożenia w liczbach zespolonych
     * @param x Obiekt klasy Complex
     * @return Wynik mnożenia obiektu wywołującego metodę przez obiekt x
     */
    @Override
    public Complex mul(Complex x) {  // Mnożenie

        double newRe = this.re * x.re - this.im * x.im;
        double newIm = this.re * x.im + this.im * x.re;

        this.re = newRe;
        this.im = newIm;

        return this;
    }

    /**
     * Metoda implementująca operację dzielenia w liczbach zespolonych
     * @param x Obiekt klasy Complex
     * @return Wynik dzielenia obiektu wywołującego metodę przez obiekt x
     * @throws DivideByZeroException Wyjątek dzielenia przez 0
     */
    @Override
    public Complex div(Complex x) throws DivideByZeroException {  // Dzielenie

        if(x.re == 0 && x.im == 0) throw new DivideByZeroException(this.toString(), x.toString());

        double newRe = (this.re * x.re + this.im * x.im)/(x.re*x.re + x.im*x.im);
        double newIm = (this.im * x.re - this.re * x.im)/(x.re*x.re + x.im*x.im);

        this.re = newRe;
        this.im = newIm;

        return this;
    }
    /**
     * Metoda implementująca operację modułu w liczbach zespolonych
     * @return Moduł obiektu wywołującego metodę
     */
    public double abs() {
        return Math.sqrt(Math.pow(this.re, 2) + Math.pow(this.im, 2));
    }
    /**
     * Metoda implementująca operację kwadratu modułu w liczbach zespolonych
     * @return Kwadrat modułu obiektu wywołującego metodę
     */
    public double sqrAbs() {
        return Math.pow(this.re, 2) + Math.pow(this.im, 2);
    }
    /**
     * Metoda implementująca operację wyliczenia argumentu liczby zespolonej
     * @return Zwraca fazę obiektu wywołującego metodę
     * @throws IndefinitePhaseException Wyjątek dla liczby zespolonej równej 0, której argument z definicji jest nieokreślony
     */
    public double phase() throws IndefinitePhaseException {
        if(this.re == 0) {
            if(this.im > 0) return Math.PI*0.5;         // zamiast dzielić przez 2 mam *0.5
            else if(this.im < 0) return -0.5*Math.PI;
            else {
                throw new IndefinitePhaseException(toString());
            }
        }
        if(this.im == 0) {
            if(this.re > 0) return 0.0;
            else if(this.re < 0) return Math.PI;
        }

        if(this.re > 0) {
            return Math.atan(im()/re());
        } else {
            return Math.atan((im()/re())+Math.PI);
        }
    }

    /**
     * Metoda zwracająca część rzeczywistą liczby zespolonej
     * @return Zwraca część rzeczywistą obiektu wywołującego metodę
     */
    public double re() {
        return this.re;
    }
    /**
     * Metoda zwracająca część urojoną liczby zespolonej
     * @return Zwraca część urojoną obiektu wywołującego metodę
     */
    public double im() {
        return this.im;
    }

    /* Metody statyczne dla powyższych operacji */

    /**
     * Metoda implementująca operację dodawania dwóch liczb zespolonych
     * @param x Obiekt klasy Complex
     * @param y Obiekt klasy Complex
     * @return Obiekt klasy Complex, będący wynikiem dodawania
     */
    public static Complex add(Complex x, Complex y) {
        Complex object = new Complex(x);
        object.add(y);

        return object;
    }
    /**
     * Metoda implementująca operację odejmowania dwóch liczb zespolonych
     * @param x Obiekt klasy Complex
     * @param y Obiekt klasy Complex
     * @return Obiekt klasy Complex, będący wynikiem odejmowania
     */
    public static Complex sub(Complex x, Complex y) {
        Complex object = new Complex(x);
        object.sub(y);

        return object;
    }
    /**
     * Metoda implementująca operację mnożenia dwóch liczb zespolonych
     * @param x Obiekt klasy Complex
     * @param y Obiekt klasy Complex
     * @return Obiekt klasy Complex, będący wynikiem mnożenia
     */
    public static Complex mul(Complex x, Complex y) {
        Complex object = new Complex(x);
        object.mul(y);

        return object;
    }
    /**
     * Metoda implementująca operację dzielenia dwóch liczb zespolonych
     * @param x Obiekt klasy Complex
     * @param y Obiekt klasy Complex
     * @return Obiekt klasy Complex, będący wynikiem dzielenia
     */
    public static Complex div(Complex x, Complex y) throws DivideByZeroException {
        Complex object = new Complex(x);
        object.div(y);

        return object;
    }
    /**
     * Metoda implementująca operację modułu liczby zespolonej
     * @param x Obiekt klasy Complex
     * @return Liczba zmiennoprzecinkowa, będąca wynikiem operacji modułu
     */
    public static double abs(Complex x) {
        return Math.sqrt(Math.pow(x.re, 2) + Math.pow(x.im, 2));

    }
    /**
     * Metoda implementująca operację kwadratu modułu liczby zespolonej
     * @param x Obiekt klasy Complex
     * @return Liczba zmiennoprzecinkowa, będąca wynikiem operacji kwadratu modułu
     */
    public static double sqrAbs(Complex x) {
        return Math.pow(x.re, 2) + Math.pow(x.im, 2);
    }
    /**
     * Metoda implementująca operację obliczania argumentu liczby zespolonej x
     * @param x Obiekt klasy Complex
     * @return Liczba zmiennoprzecinkowa, będąca wynikiem operacji obliczania fazy liczby zespolonej x
     * @throws IndefinitePhaseException Wyjątek dla liczby zespolonej równej 0, której argument z definicji jest nieokreślony
     */
    public static double phase(Complex x) throws IndefinitePhaseException {
        if(x.re == 0) {
            if(x.im > 0) return Math.PI*0.5;         // zamiast dzielić przez 2 mam *0.5
            else if(x.im < 0) return -0.5*Math.PI;
            else {
                throw new IndefinitePhaseException(x.toString());
            }
        }
        if(x.im == 0) {
            if(x.re > 0) return 0.0;
            else if(x.re < 0) return Math.PI;
        }

        double a = x.im()/x.re();

        if(x.re > 0) {
            return Math.atan(a);
        } else {
            return Math.atan(a+Math.PI);
        }
    }
    public static double re(Complex x) {
        return x.re();
    }
    public static double im(Complex x) {
        return x.im();
    }
    /**
     * Metoda konwertująca obiekt Complex do postaci String
     * @return Liczba zespolona w postaci ciągu znaków
     */
    @Override
    public String toString() {
        double x = re();
        double y = im();

        if(x > 0) {
            if(y == 1) {
                return x + "+i";
            } else if(y == -1) {
                return x + "-i";
            } else {
                if(y > 0) return x + "+" + y + "i";
                else if (y < 0) return x + (y + "i");
                else return Double.toString(x);
            }
        } else if(x < 0) {
            if(y == 1) {
                return x + "+i";
            } else if(y == -1) {
                return x + "-i";
            } else {
                if(y > 0) return x + "+" + y + "i";
                else if (y < 0) return x + (y + "i");
                else return Double.toString(x);
            }
        } else {
            if(y == 1) {
                return "i";
            } else if(y == -1) {
                return "-i";
            } else {
                if(y != 0) return y + "i";
                else return "0";
            }
        }
    }
    /**
     * Metoda zamienia ciąg znaków na liczbę zespoloną
     * @param obj Obiekt klasy String
     * @return Liczba zespolona w postaci obiektu String o wartości podanej w argumencie
     * @throws NotAComplexNumberException Wyjątek dla argumentu, który nie reprezentuje żadnej liczby zespolonej
     */
    public static Complex valueOf(String obj) throws NotAComplexNumberException {

        obj = obj.trim();

        int i = 0, start = 0, lenght = obj.length();
        String real = "0", imaginary = "0";
        boolean end = false, re = false, im = false, dot = false, sign = false, half = false;

        if(lenght > 1) {
            while(!end) {
                if(re || im) dot = false;

                if(i > lenght-1) {
                    if(im) {
                        if(sign) {
                            real = obj.substring(start, i);
                        }
                        end = true;

                    } else {
                        real = obj.substring(start, i);
                        end = true;
                    }
                } else {
                    char c = obj.charAt(i);

                    // jest + lub -
                    if(c == 43 || c == 45) {
                        if(i != start) {
                            if(!sign) {
                                if(im) {
                                    sign = true;
                                    i++;
                                } else {
                                    re = true;
                                    real = obj.substring(start, i);
                                    sign = true;
                                    start = i;
                                }
                            } else throw new NotAComplexNumberException(obj);
                        } else {
                            if(im) sign = true;
                            i++;
                        }

                        // jest i
                    } else if(c == 105) {
                        if(!im) {
                            if(i == start) {
                                imaginary = "1";
                                half = true;
                            } else if(i == (start + 1)) {
                                char cz = obj.charAt(i-1);
                                if(cz == '+') {
                                    imaginary = "1";
                                    half = true;
                                }
                                else if(cz == '-') {
                                    imaginary = "-1";
                                    half = true;
                                }
                                else if(cz == '.') throw new NotAComplexNumberException(obj);
                                else {
                                    imaginary = Character.toString(cz);
                                }
                            } else {
                                imaginary = obj.substring(start, i);
                                half = true;
                            }

                            im = true;
                            i++;
                            start = i;
                        } else {
                            throw new NotAComplexNumberException(obj);
                        }

                        // jest .
                    } else if (c == 46) {
                        if(!dot) {
                            dot = true;
                            i++;
                        }
                        else throw new NotAComplexNumberException(obj);
                        // jest literą
                    } else if (c < 48 || c > 57) {
                        throw new NotAComplexNumberException(obj);
                    } else {
                        i++;
                    }

                    end = re && im;
                }
            }

        } else if (lenght == 1) {
            char c = obj.charAt(0);

            // Jest liczbą dodatnią
            if(c >= 48 && c <= 57) {
                real = Character.toString(c);
                // Znaleźliśmy liczbe
                end = true;

                // Jest literą i
            } else if(c == 105) {
                imaginary = "1";
                // Znaleźliśmy liczbe
                end = true;

                // Jest jakimś innym znakiem
            } else {
                throw new NotAComplexNumberException(obj);
            }
        } else {
            throw new NotAComplexNumberException(obj);
        }

        double x = Double.parseDouble(real);
        double y = Double.parseDouble(imaginary);

        return new Complex(x,y);
    }
    /**
     * Metoda przypisuje podaną wartość części rzeczywistej
     * @param x Liczba zmiennoprzecinkowa podwójnej precyzji
     */

    public void setRe(double x) {
        this.re = x;
    }
    /**
     * Metoda przypisuje podaną wartość części urojonej
     * @param x Liczba zmiennoprzecinkowa podwójnej precyzji
     */
    public void setIm(double x) {
        this.im = x;
    }
    /**
     * Metoda przypisuje aktualnemu obiektowi klasy Complex wartości argumentu x
     * @param x Obiekt klasy Complex
     */
    public void setVal(Complex x) {
        this.re = x.re;
        this.im = x.im;
    }
    /**
     * Metoda przypisuje zmiennym re i im aktualnemu obiektowi klasy Complex, odpowiednio wartości argumentu x i y
     * @param x Liczba zmiennoprzecinkowa podwójnej precyzji
     * @param y Liczba zmiennoprzecinkowa podwójnej precyzji
     */
    /* Przypisuje podaną wartość */
    public void setVal(double x, double y) {
        this.re = x;
        this.im = y;
    }

}