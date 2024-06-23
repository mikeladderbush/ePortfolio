package mikeladderbush.BjjSite.BjjSite.Database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class DatabaseConnection {

    public Connection connectToDatabase(String databaseName) {
        Connection conn = null;
        String url = "jdbc:sqlite:" + databaseName; // Removed hardcoded path
        try {
            conn = DriverManager.getConnection(url);
            if (conn != null) {
                try (Statement stmt = conn.createStatement()) {
                    stmt.execute("PRAGMA foreign_keys = ON");
                    DatabaseStatement databaseStatement = new DatabaseStatement();
                    databaseStatement.defineTables(conn);
                }
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return conn;
    }
}
