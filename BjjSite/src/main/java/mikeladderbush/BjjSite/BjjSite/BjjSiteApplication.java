package mikeladderbush.BjjSite.BjjSite;

import java.sql.Connection;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

import mikeladderbush.BjjSite.BjjSite.Classes.User;
import mikeladderbush.BjjSite.BjjSite.Database.DatabaseConnection;
import mikeladderbush.BjjSite.BjjSite.Database.DatabaseStatement;
import mikeladderbush.BjjSite.BjjSite.Factories.UserFactory;
import mikeladderbush.BjjSite.BjjSite.Services.UserService;

@SpringBootApplication
public class BjjSiteApplication {
	public static void main(String[] args) {
		SpringApplication.run(BjjSiteApplication.class, args);
	}

	@Bean
	public DatabaseConnection databaseConnection() {
		return new DatabaseConnection();
	}

	@Bean
	public Connection connection(DatabaseConnection dbConnection) {
		Connection conn = dbConnection.connectToDatabase("test.db");
		DatabaseStatement dbStatement = new DatabaseStatement();
		dbStatement.defineTables(conn);
		return conn;
	}

	@Bean
	public UserService userService() {
		return new UserService(null);
	}

	@Bean
	public UserFactory userFactory() {
		return new UserFactory(userService());
	}

	@Bean
	public void demo(Connection conn, UserFactory userFactory, UserService userService) {
		User testUser = userFactory.createUser(builder -> {
			builder
					.firstName("Mike")
					.lastName("Ladderbush")
					.username("Mikel123")
					.password("Applesauce1%")
					.email("mikeladderbush@gmail.com")
					.phone("9787708430")
					.address("160 Cottage Street")
					.sex("Male")
					.dob("2/24/97")
					.paymentOptions(null);
		});

		DatabaseStatement.insertRecords(conn, testUser);
	}
}
