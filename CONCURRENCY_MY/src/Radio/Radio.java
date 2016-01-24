package Radio;

import javafx.scene.layout.Pane;

import javax.swing.*;
import java.applet.Applet;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by ChrisSnowden on 23/01/2016.
 */
public class Radio extends Applet {

    RadioController controller;
    RadioDisplay display;
    Button on_off;
    Button scan;
    Button reset;

    @Override
    public void init() {
        setLayout(new BorderLayout());
        display = new RadioDisplay();
        controller = new RadioController(display);
        add("Center",display);

        on_off = new Button("On/Off");
        on_off.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.on_off();            }
        });

        scan = new Button("Scan");
        scan.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.scan();
            }
        });

        reset = new Button("Reset");
        reset.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.reset();
            }
        });

        Panel p = new Panel();
        p.setLayout(new FlowLayout());
        p.add(on_off);
        p.add(scan);
        p.add(reset);
        add("South",p);
    }

    @Override
    public void stop() {
        controller.on_off();
    }
}