package core;

import interfaces.ControlInterface;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Random;

import core.Common.State;

public class SystemController implements ControlInterface {

    private State mode = State.AUTOMATIC;
    private int valve = 0;
    private boolean connected = true;
    private float waterLevel;
    private long lastMessageTimeFromTMS;
    private List<Integer> measuramentsValues = new LinkedList<>(Collections.nCopies(100, 0)); //create a list of 100 elements, all 0

    private Random rand = new Random();

    @Override
    public synchronized State getState() {
        return mode;
    }

    @Override
    public synchronized void setState(State mode) {
        this.mode = mode;
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
    public void setWaterLevel(float waterLevel) {
        this.waterLevel = waterLevel;
        this.measuramentsValues.removeFirst();
        this.measuramentsValues.addLast((int)waterLevel);
    }

    @Override
    public void setLastMessageTimeFromTMS(long time) {
        this.lastMessageTimeFromTMS = time;
    }

    @Override
    public float getWaterLevel() {
        return this.waterLevel;
    }

    @Override
    public long getLastMessageTimeFromTMS() {
        return this.lastMessageTimeFromTMS;
    }
}
