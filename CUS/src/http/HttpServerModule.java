package http;

import com.sun.net.httpserver.HttpServer;
import interfaces.ControlInterface;

import java.net.InetSocketAddress;

public class HttpServerModule {

    private HttpServer server;
    private ControlInterface controller;

    public HttpServerModule(int port, ControlInterface controller) throws Exception {

        this.controller = controller;

        //creating the server
        server = HttpServer.create(
                new InetSocketAddress(port),
                0
        );

        //creating an handler for every possible request of the client
        //ex: a request comming for /api/status create and execute StatusHandler
        server.createContext(
                "/api/status",
                new StatusHandler(this.controller)
        );

        server.createContext(
                "/api/measurements",
                new MeasurementsHandler(this.controller)
        );

        server.createContext(
                "/api/mode",
                new ModeHandler(this.controller)
        );

        server.createContext(
                "/api/valve",
                new ValveHandler(this.controller)
        );

        server.setExecutor(null);   //se the default thread pool, Java can manage more client and more request 
    }

    public void start() {
        server.start();
        System.out.println("Server HTTP started on port 8080");
    }

    public void stop() {
        server.stop(0);
    }
}
