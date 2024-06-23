package mikeladderbush.BjjSite.BjjSite.Services;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Random;

import mikeladderbush.BjjSite.BjjSite.Classes.Session;
import mikeladderbush.BjjSite.BjjSite.Interfaces.ServiceInterface;

/**
 * Manages operations related to Sessions.
 */
public class SessionService implements ServiceInterface {

    private List<Session> Sessions;

    /**
     * Constructs a SessionService with an empty list of Sessions.
     */
    public SessionService() {
        this.Sessions = new ArrayList<>();
    }

    /**
     * Adds a Session to the list of Sessions.
     * 
     * @param Session The Session to add.
     */
    public void addSession(Session session) {
        Sessions.add(session);
    }

    /**
     * Generates a random ID for Sessions.
     * 
     * @return A randomly generated ID for Sessions.
     */
    public String generateId() {
        return ServiceInterface.super.generateId();
    }

    /**
     * Deletes a Session with the specified ID.
     * 
     * @param id The ID of the Session to delete.
     */
    public void deleteSession(String id) {
        Iterator<Session> iterator = Sessions.iterator();
        while (iterator.hasNext()) {
            Session Session = iterator.next();
            if (Session.getId().equals(id)) {
                iterator.remove();
            }
        }
    }

    /**
     * Retrieves all Sessions.
     * 
     * @return A list of all Sessions.
     */
    public List<Session> getAllSessions() {
        return Sessions;
    }

    /**
     * Finds and retrieves a Session by its ID.
     * 
     * @param id The ID of the Session to find.
     * @return The Session with the specified ID, or null if not found.
     */
    public Session findSessionById(String id) {
        for (Session Session : Sessions) {
            if (Session.getId().equals(id)) {
                return Session;
            }
        }
        return null;
    }
}
