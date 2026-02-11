package core;

public class Common {

    public static final int L1 = 1;
    public static final double L2 = 1.8;
    public static final int T1 = 1000;
    public static final int T2 = 5000;

    public enum State{
        AUTOMATIC,
        MANUAL,
        UNCONNECTED
    }

    public enum AutomaticState {
        WAIT,
        L1_SURPASSED,
        L2_SURPASSED
    }

    public static String stateToString(State s){
        switch (s) {
            case State.AUTOMATIC:
                return "AUTOMATIC";
            case State.MANUAL:
                return "MANUAL";
            case State.UNCONNECTED:
                return "UNCONNECTED";
            default:
                return "";
        }
    }

    public static State stringToState(String s){
        switch (s) {
            case "AUTOMATIC":
                return State.AUTOMATIC;
            case "MANUAL":
                return State.MANUAL;
            case "UNCONNECTED":
                return State.UNCONNECTED;
            default:
                return null;
        }
    }
}
