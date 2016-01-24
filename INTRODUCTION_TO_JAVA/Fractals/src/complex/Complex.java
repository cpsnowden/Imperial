package complex;

/**
 * Created by ChrisSnowden on 16/01/2016.
 */
public class Complex {

    private double a;
    private double b;

    public Complex(double a, double b) {

        this.a = a;
        this.b = b;

    }

    public static Complex sum(Complex c1, Complex c2) {
        return new Complex(c1.a + c2.a, c1.b + c2.b);
    }

    public static Complex multiply(Complex c1, Complex c2) {
        return new Complex(c1.a * c2.a - c1.b * c2.b, c1.a * c2.b + c1.b * c2.a);
    }

    public double magnitudeSquared(){
        return a*a + b*b;
    }


}
