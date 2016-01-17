package mandelbrot;

import complex.Complex;
/**
 * Created by ChrisSnowden on 16/01/2016.
 */

public class MandelbrotSet {

    private static final double DIV_THRESH = 2.0;
    private static final double DIV_THRESH_SQRD = DIV_THRESH * DIV_THRESH;

    private int max_escape;

    public MandelbrotSet(int max_escape) {
        this.max_escape = max_escape;
    }
    private int escapeValue(Complex c) {

        Complex t = c;

        for(int i = 0; i < max_escape; i++) {
            if(t.magnitudeSquared() > DIV_THRESH_SQRD)
                return i;
            t = Complex.sum(Complex.multiply(t,t),c);
        }
        return max_escape;
    }

    public boolean contains(Complex z) {
        return escapeValue(z) == max_escape;
    }

    public double escapeVl(Complex z) {
        return 1 - escapeValue(z) / (double) max_escape;
    }
}
