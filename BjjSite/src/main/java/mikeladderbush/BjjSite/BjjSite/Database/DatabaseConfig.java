package mikeladderbush.BjjSite.BjjSite.Database;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import java.sql.Connection;
import java.sql.SQLException;
import mikeladderbush.BjjSite.BjjSite.Database.DatabaseConnection;

@Configuration
public class DatabaseConfig {

    @Bean
    public Connection connection() throws SQLException {
        DatabaseConnection databaseConnection = new DatabaseConnection();
        return databaseConnection.connectToDatabase("your_database_file.db"); // Specify your database file name
    }
}
