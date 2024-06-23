package mikeladderbush.BjjSite.BjjSite.Factories;

import java.util.function.Consumer;

import mikeladderbush.BjjSite.BjjSite.Classes.Session;
import mikeladderbush.BjjSite.BjjSite.Services.SessionService;

import java.util.Date;

public class SessionFactory {

    private static final SessionService sessionService = new SessionService();

    // Method to create a Session with default values
    public static Session createSession() {
        String id = sessionService.generateId();
        String sessionType = "REGULAR CLASS";
        String timeOfSession = "6:00PM";
        Date dateOfSession = new Date();
        return new Session.SessionBuilder<>(id, sessionType, timeOfSession, dateOfSession).buildSession();
    }

    public static Session createSession(Consumer<Session.SessionBuilder<?>> consumer) {
        String id = sessionService.generateId();
        String sessionType = "REGULAR CLASS";
        String timeOfSession = "6:00PM";
        Date dateOfSession = new Date();
        Session.SessionBuilder<?> builder = new Session.SessionBuilder<>(id, sessionType, timeOfSession, dateOfSession);
        consumer.accept(builder);
        return builder.buildSession();
    }
}
