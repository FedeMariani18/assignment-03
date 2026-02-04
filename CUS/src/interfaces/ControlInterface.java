package interfaces;

import java.util.List;
import core.Common.*;

public interface ControlInterface {

    State getState();              // MANUAL / AUTOMATIC / UNCONNECTED

    void setState(State mode);

    int getValveOpening();

    void setValveOpening(int value);

    boolean isConnected();

    List<Integer> getMeasurements(int n);
}