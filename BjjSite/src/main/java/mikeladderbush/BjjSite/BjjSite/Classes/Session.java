package mikeladderbush.BjjSite.BjjSite.Classes;


import java.util.Date;

/**
 * Represents a Training Session.
 */
public class Session {

    protected String id;
    protected String sessionType;

    // Eventually set to a date/time that works best with database.
    private String timeOfSession;
    private Date dateOfSession;

    protected Session(SessionBuilder<?> SessionBuilder) {
        id = SessionBuilder.id;
        sessionType = SessionBuilder.sessionType;
        timeOfSession = SessionBuilder.timeOfSession;
        dateOfSession = SessionBuilder.dateOfSession;
    }

    public static class SessionBuilder<T extends SessionBuilder<T>> {

        private String id;
        private String sessionType;
        private String timeOfSession;
        private Date dateOfSession;

        public SessionBuilder(String id, String sessionType, String timeOfSession, Date dateOfSession) {
            this.id = id;
            this.sessionType = sessionType;
            this.timeOfSession = timeOfSession;
            this.dateOfSession = dateOfSession;
        }

        protected T self() {
            return (T) this;
        }

        public Session buildSession() {
            return new Session(this);
        }
    }

    /**
     * Retrieves the ID of the Session.
     * 
     * @return The ID of the Session.
     */
    public String getId() {
        return id;
    }

    /**
     * For testing purpose only.
     * 
     * @param id
     */
    public void setId(String id) {
        this.id = id;
    }

    public String getSessionType() {
        return sessionType;
    }

    public void setSessionType(String sessionType) {
        this.sessionType = sessionType;
    }

    public String getTimeOfSession() {
        return timeOfSession;
    }

    public void setTimeOfSession(String timeOfSession) {
        this.timeOfSession = timeOfSession;
    }

    public Date getDateOfSession() {
        return dateOfSession;
    }

    public void setDateOfSession(Date dateOfSession) {
        this.dateOfSession = dateOfSession;
    }

}
