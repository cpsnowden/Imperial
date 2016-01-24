package Radio;

import com.sun.org.apache.xerces.internal.impl.dv.xs.BooleanDV;
import com.sun.org.apache.xpath.internal.operations.Bool;

import java.awt.*;

/**
 * Created by ChrisSnowden on 24/01/2016.
 */
public class RadioDisplay extends Canvas {

    private int frequency = 0;
    private Font small = new Font("Helvetica",Font.BOLD,14);
    private Font big = new Font("Helvetica",Font.BOLD,18);
    private Boolean on = false;

    public RadioDisplay() {
        super();
        setSize(150,260);
    }
    private final static int botY = 200;

    @Override
    public void paint(Graphics g) {
        update(g);
    }

    Graphics offgraphics;
    Image offscreen;
    Dimension offscreensize;

    @Override
    public void update(Graphics g) {
        backdrop();

        offgraphics.setColor(Color.white);
        offgraphics.setFont(big);
        offgraphics.setFont(small);

        if (on) {
            offgraphics.drawString("On", 20, botY + 15);
            offgraphics.drawString("Frequency: " + String.valueOf(frequency), 10, 55);
        } else
            offgraphics.drawString("Off",20,botY+15);
        if (on)
            offgraphics.setColor(Color.green);
        else
            offgraphics.setColor(Color.red);
        offgraphics.fillArc(90,botY,20,20,0,360);

        g.drawImage(offscreen, 0, 0, null);

    }

    public void setF(int frequency) {
        this.frequency = frequency;
        repaint();
    }


    public void backdrop() {
        Dimension d = getSize();
        if ((offscreen == null) || (d.width != offscreensize.width)
                || (d.height != offscreensize.height)) {
            offscreen = createImage(d.width, d.height);
            offscreensize = d;
            offgraphics = offscreen.getGraphics();
        }
        offgraphics.setColor(Color.black);
        offgraphics.fillRect(0, 0, getSize().width, getSize().height);
        offgraphics.setColor(Color.white);
        offgraphics.drawRect(5,10,getSize().width-15,getSize().height-40);
        offgraphics.setColor(Color.blue);
        offgraphics.fillRect(6,11,getSize().width-17,getSize().height-42);
    }

    public void off() {
        this.on = false;
        repaint();
    }

    public void on() {
        this.on = true;
        repaint();
    }
}
