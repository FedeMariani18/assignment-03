package http;

import com.sun.net.httpserver.*;
import interfaces.ControlInterface;

import java.io.InputStream;

public class ValveHandler implements HttpHandler {

    private ControlInterface controller;

    public ValveHandler(ControlInterface controller) {
        this.controller = controller;
    }

    @Override
    public void handle(HttpExchange exchange) {

        try {

            if (!exchange.getRequestMethod().equals("POST")) {
                exchange.sendResponseHeaders(405, -1);
                return;
            }

            if (!controller.getMode().equals("MANUAL")) {
                exchange.sendResponseHeaders(403, -1);
                return;
            }

            InputStream is = exchange.getRequestBody();
            String body = new String(is.readAllBytes());

            int value =
                    Integer.parseInt(body.replaceAll("\\D+", ""));

            controller.setValveOpening(value);

            exchange.sendResponseHeaders(200, -1);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
