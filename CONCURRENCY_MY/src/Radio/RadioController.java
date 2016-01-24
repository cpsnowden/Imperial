package Radio;

/**
 * Created by ChrisSnowden on 24/01/2016.
 */
public class RadioController implements Runnable {

    public enum State {ON, OFF, SCANNING, LOCKED};
    State state = State.OFF;
    Thread fController;

    private int frequency = 108;
    private FControl fControl;
    private RadioDisplay display;

    public RadioController(RadioDisplay display) {
        this.display = display;
    }

    synchronized void reset() {
        if(state == State.ON) {
            fController = new Thread(this);
            fController.start();
        }
    }

    synchronized public void scan() {
        if(state == State.ON && state != State.SCANNING) {
            state = State.SCANNING;
            fController = new Thread(this);
            fController.start();
        }
    }

    synchronized  void on_off() {

        if(state != State.OFF) {
            state = State.OFF;
            display.off();
        }
        else {
            state = State.ON;
            this.reset();
            display.on();

        }
    }

    @Override
    synchronized public void run() {
        try {
            if(state == State.ON) {
                frequency = 108;
                display.setF(frequency);
            } else if(state == State.SCANNING) {
                while(frequency >= 88) {
                    --frequency;
                    display.setF(frequency);
                    if(frequency % 4 == 0)
                       break;
                    wait(200);
                }
                state = State.ON;
            }
        } catch (InterruptedException e) {}
    }
}
