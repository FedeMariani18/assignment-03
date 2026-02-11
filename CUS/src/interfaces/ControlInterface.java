package interfaces;

import java.util.List;
import core.Common.*;

public interface ControlInterface {

    State getState();              // MANUAL / AUTOMATIC / UNCONNECTED

    void setState(State mode);

    int getValveOpening();

    void setValveOpening(int value);

    boolean isConnected();

    List<Float> getMeasurements(int n);

    void setWaterLevel(float waterLevel);

    float getWaterLevel();

    void checkT2();

}