package mandelbrot;

import complex.Complex;
import org.w3c.dom.css.Rect;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.util.*;
import java.util.List;

/**
 * Created by ChrisSnowden on 16/01/2016.
 */
public class MandelbrotCanvas extends JComponent {

    private static final int WHITE_RGB = 0b111111111111111111111111;
    private static final int BLACK_RGB = 0;
    private static final int DEFAULT_HEIGHT = 384;
    private static final int DEFAULT_WIDTH = 512;
    private static final int ZOOM = 2;
    private static final int THREADS = 32;

    private MandelbrotSet m;
    private double centreX = -0.75;
    private double centreY = 0;
    private double pxScale = 0.005;
    BufferedImage image;

    public MandelbrotCanvas(MandelbrotSet m) {
        super();
        this.m = m;

        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                centreX = getMinReal() + (e.getX() * pxScale);
                centreY = getMaxIm() - (e.getY() * pxScale);
                MandelbrotCanvas.this.repaint();
            }
        });

        getInputMap(WHEN_IN_FOCUSED_WINDOW).put(
                KeyStroke.getKeyStroke("typed +"), "zoomIn");
        getActionMap().put("zoomIn", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                MandelbrotCanvas.this.pxScale /= ZOOM;
                MandelbrotCanvas.this.repaint();
            }
        });


        getInputMap(WHEN_IN_FOCUSED_WINDOW).put(
                KeyStroke.getKeyStroke("typed -"), "zoomOut");
        getActionMap().put("zoomOut", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                MandelbrotCanvas.this.pxScale *= ZOOM;
                MandelbrotCanvas.this.repaint();
            }
        });

    }


    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        int w = getWidth();
        int h = getHeight();

        image = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);

        List<Rectangle> areas = new LinkedList<>();
        areas.add(new Rectangle(w, h));

        for( int i = THREADS / 2; i > 0; i/=2) {
            List<Rectangle> tmp = new LinkedList<>();

            for(Rectangle r : areas) {
                tmp .addAll(splitRect(r));
            }

            areas = tmp;
        }

        List<Thread> painters = new LinkedList<>();

        for(Rectangle r : areas) {
            Thread t = new TileThread(r);
            painters.add(t);
            t.start();
        }

        try{
            for(Thread t : painters) {
                t.join();
            }
        } catch (InterruptedException e){
            e.printStackTrace();
        }

        g.drawImage(image, 0, 0, null);
    }

    public class TileThread extends Thread {
        private Rectangle r;

        public TileThread(Rectangle r) {
            this.r = r;
        }

        @Override
        public void run() {

            Complex z = null;
            double a = getMinReal();
            double b = getMaxIm();
            int xMax = r.x + r.width;
            int yMax = r.y + r.height;
            int rgb = 0;
            double eV = 0;
            for( int x = 0; x < xMax; x++) {
                for( int y = 0; y < yMax; y++) {
                    z = new Complex(a + (x * pxScale), b - (y *pxScale));
//                    rgb = WHITE_RGB;
                    //if(m.contains(z)) /*{*/
                      // rgb = BLACK_RGB;
//                    } else {
                        eV = m.escapeVl(z);

                       rgb = (int) (eV  * WHITE_RGB);
                    //    System.out.println(eV);
                    //}

                    image.setRGB(x,y, rgb);

                }
            }

        }
    }


    private List<Rectangle> splitRect(Rectangle r) {
        List<Rectangle> halves = new LinkedList<>();

        if(r.width > r.height) {
            halves.add(new Rectangle(
                    r.x,
                    r.y,
                    r.width / 2,
                    r.height));
            halves.add(new Rectangle(
                    r.x + r.width / 2,
                    r.y,
                    r.width - r.width / 2,
                    r.height));
        } else {
            halves.add(new Rectangle(
                    r.x,
                    r.y,
                    r.width,
                    r.height / 2));
            halves.add(new Rectangle(
                    r.x,
                    r.y + r.height / 2,
                    r.width,
                    r.height - r.height / 2));
        }

        return halves;
    }










    private double getMaxIm() {
        return (centreY + (( 1 - (getHeight() % 2)) * pxScale * 0.5)) + ((getHeight() / 2) * pxScale);
    }

    private double getMinReal() {
        return (centreX - (( 1 - (getWidth() % 2)) * pxScale * 0.5)) - ((getWidth() / 2) * pxScale);
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    }




}
