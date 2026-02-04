package core;

public class Common {
    public enum State{
        AUTOMATIC,
        MANUAL,
        UNCONNECTED
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
