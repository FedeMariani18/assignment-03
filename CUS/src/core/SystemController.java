package core;

import interfaces.ControlInterface;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

import core.Common.AutomaticState;
import core.Common.State;

public class SystemController implements ControlInterface {

    private State mode = State.UNCONNECTED;
    private AutomaticState automaticState = AutomaticState.WAIT;
    private long sinceL1;
    private int valve = 0;
    private boolean connected = true;
    private float waterLevel;
    private long lastMessageTimeFromTMS;
    private List<Integer> measuramentsValues = new LinkedList<>(Collections.nCopies(100, 0)); //create a list of 100 elements, all 0

    @Override
    public synchronized State getState() {
        return mode;
    }

    @Override
    public synchronized void setState(State mode) {
        if (this.mode != mode) {
            if (mode == State.AUTOMATIC) {
                this.automaticState = AutomaticState.WAIT;
            }
            this.mode = mode;
        }
    }

    @Override
    public synchronized int getValveOpening() {
        return valve;
    }

    @Override
    public synchronized void setValveOpening(int value) {
        if (mode == State.MANUAL) {
            valve = value;
        }
    }

    @Override
    public synchronized boolean isConnected() {
        return connected;
    }

    @Override
    public synchronized List<Integer> getMeasurements(int n) {
        int size = measuramentsValues.size();
        List<Integer> lastN = measuramentsValues.subList(Math.max(0, size - n), size);
        return lastN;
    }

    @Override
    public synchronized void setWaterLevel(float waterLevel) {
        if (mode == State.UNCONNECTED) {
            this.mode = State.AUTOMATIC;
            this.automaticState = AutomaticState.WAIT;
        }

        this.waterLevel = waterLevel;
        this.measuramentsValues.removeFirst();
        this.measuramentsValues.addLast((int)waterLevel);

        long now = System.currentTimeMillis();
        this.lastMessageTimeFromTMS = now;

        if (mode == State.MANUAL) {
            return;
        }

        switch (automaticState) {
            case AutomaticState.WAIT:
                if (this.waterLevel > Common.L1) {
                    automaticState = AutomaticState.L1_SURPASSED;
                    sinceL1 = now;
                }
                break;
            case AutomaticState.L1_SURPASSED:
                if (this.waterLevel > Common.L2) {
                    automaticState = AutomaticState.L2_SURPASSED;
                    this.valve = 100;
                } else if (this.waterLevel < Common.L1) {
                    automaticState = AutomaticState.WAIT;
                    this.valve = 0;
                }  else if (now - sinceL1 > Common.T1) {
                    this.valve = 50;
                }
                break;
            case AutomaticState.L2_SURPASSED:
                if (this.waterLevel < Common.L2) {
                    automaticState = AutomaticState.L1_SURPASSED;
                    this.valve = 50;
                    sinceL1 = now;
                }
                break;
        }
    }

    @Override
    public synchronized float getWaterLevel() {
        return this.waterLevel;
    }

    @Override
    public synchronized void checkT2() {
        long now = System.currentTimeMillis();
        if (this.mode == State.UNCONNECTED) {
            return;
        }
        if (now - this.lastMessageTimeFromTMS > Common.T2) {
            this.mode = State.UNCONNECTED;
        }
    }

}
