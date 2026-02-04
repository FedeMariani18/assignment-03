package http;

import com.sun.net.httpserver.*;
import interfaces.ControlInterface;

import java.io.InputStream;

public class ModeHandler implements HttpHandler {

    private ControlInterface controller;

    public ModeHandler(ControlInterface controller) {
        this.controller = controller;
    }

    @Override
    public void handle(HttpExchange exchange) {

        try {

            if (!exchange.getRequestMethod().equals("POST")) {
                exchange.sendResponseHeaders(405, -1);
                return;
            }

            InputStream is = exchange.getRequestBody();
            String body = new String(is.readAllBytes());

            if (body.contains("MANUAL")) {
                controller.setMode("MANUAL");
            }
            else if (body.contains("AUTOMATIC")) {
                controller.setMode("AUTOMATIC");
            }

            exchange.sendResponseHeaders(200, -1);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
