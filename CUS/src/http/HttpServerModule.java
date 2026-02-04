package http;

import com.sun.net.httpserver.HttpServer;
import interfaces.ControlInterface;

import java.net.InetSocketAddress;

public class HttpServerModule {

    private HttpServer server;
    private ControlInterface controller;

    public HttpServerModule(
            int port,
            ControlInterface controller
    ) throws Exception {

        this.controller = controller;

        server = HttpServer.create(
                new InetSocketAddress(port),
                0
        );

        server.createContext(
                "/api/status",
                new StatusHandler(controller)
        );

        server.createContext(
                "/api/measurements",
                new MeasurementsHandler(controller)
        );

        server.createContext(
                "/api/mode",
                new ModeHandler(controller)
        );

        server.createContext(
                "/api/valve",
                new ValveHandler(controller)
        );

        server.setExecutor(null);
    }

    public void start() {
        server.start();
    }

    public void stop() {
        server.stop(0);
    }
}
