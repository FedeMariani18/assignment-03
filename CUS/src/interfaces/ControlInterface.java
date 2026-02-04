package interfaces;

import java.util.List;

public interface ControlInterface {

    String getMode();              // MANUAL / AUTOMATIC / UNCONNECTED

    void setMode(String mode);

    int getValveOpening();

    void setValveOpening(int value);

    boolean isConnected();

    List<Integer> getMeasurements(int n);
}