import core.SystemController;
import http.HttpServerModule;

public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
        SystemController core = new SystemController();
        
        HttpServerModule http = new HttpServerModule(8080, core);
        http.start();
    }
}
