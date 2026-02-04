package interfaces;

import java.util.List;
import core.Common.*;

public interface ControlInterface {

    State getMode();              // MANUAL / AUTOMATIC / UNCONNECTED

    void setMode(State mode);

    int getValveOpening();

    void setValveOpening(int value);

    boolean isConnected();

    List<Integer> getMeasurements(int n);
}