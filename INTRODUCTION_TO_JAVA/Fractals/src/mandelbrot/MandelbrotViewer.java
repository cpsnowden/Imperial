package mandelbrot;

import javax.swing.*;

/**
 * Created by ChrisSnowden on 16/01/2016.
 */
public class MandelbrotViewer implements Runnable {

    public static void main (String[] args) {
        javax.swing.SwingUtilities.invokeLater(new MandelbrotViewer());
    }

    @Override
    public void run() {
        JFrame frame = new JFrame("Mandelbrot Viewer");
        MandelbrotSet model = new MandelbrotSet(100);
        MandelbrotCanvas canvas = new MandelbrotCanvas(model);
        frame.add(canvas);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

}
