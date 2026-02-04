package http;

import com.sun.net.httpserver.*;
import interfaces.ControlInterface;

import java.io.OutputStream;
import java.util.List;

public class MeasurementsHandler implements HttpHandler {

    private ControlInterface controller;

    public MeasurementsHandler(ControlInterface controller) {
        this.controller = controller;
    }

    @Override
    public void handle(HttpExchange exchange) {

        try {

            if (!exchange.getRequestMethod().equals("GET")) {
                exchange.sendResponseHeaders(405, -1);
                return;
            }

            int n = 20;

            String q = exchange.getRequestURI().getQuery();

            if (q != null && q.startsWith("last=")) {
                n = Integer.parseInt(q.substring(5));
            }

            List<Integer> values =
                    controller.getMeasurements(n);

            StringBuilder json = new StringBuilder("[");

            for (int i = 0; i < values.size(); i++) {
                json.append(values.get(i));

                if (i < values.size() - 1)
                    json.append(",");
            }

            json.append("]");

            exchange.getResponseHeaders()
                    .add("Content-Type", "application/json");

            exchange.sendResponseHeaders(200, json.length());

            OutputStream os = exchange.getResponseBody();
            os.write(json.toString().getBytes());
            os.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
