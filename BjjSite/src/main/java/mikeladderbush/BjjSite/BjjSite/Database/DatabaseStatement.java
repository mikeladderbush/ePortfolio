package mikeladderbush.BjjSite.BjjSite.Database;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import mikeladderbush.BjjSite.BjjSite.Classes.Administrator;
import mikeladderbush.BjjSite.BjjSite.Classes.Employee;
import mikeladderbush.BjjSite.BjjSite.Classes.User;

public class DatabaseStatement {

    public void defineTables(Connection conn) {
        if (conn != null) {
            try (PreparedStatement statement = conn.prepareStatement("")) {
                statement.execute("PRAGMA foreign_keys = ON");

                // Create Users Table
                String userTable = "CREATE TABLE IF NOT EXISTS users ("
                        + "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        + "firstName TEXT NOT NULL, "
                        + "lastName TEXT NOT NULL, "
                        + "username TEXT NOT NULL, "
                        + "password TEXT NOT NULL, "
                        + "email TEXT NOT NULL, "
                        + "phone TEXT, "
                        + "address TEXT, "
                        + "sex TEXT, "
                        + "dob TEXT, "
                        + "permissions TEXT"
                        + ");";
                statement.execute(userTable);

                // Create Employees Table
                String employeeTable = "CREATE TABLE IF NOT EXISTS employees ("
                        + "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        + "userId INTEGER NOT NULL, "
                        + "socialSecurityNumber TEXT NOT NULL, "
                        + "position TEXT NOT NULL, "
                        + "payrate DOUBLE NOT NULL, "
                        + "paybasis TEXT NOT NULL, "
                        + "baseEarnings DOUBLE NOT NULL, "
                        + "FOREIGN KEY (userId) REFERENCES users(id) ON DELETE CASCADE"
                        + ");";
                statement.execute(employeeTable);

                // Create Administrators Table
                String administratorTable = "CREATE TABLE IF NOT EXISTS administrators ("
                        + "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        + "userId INTEGER NOT NULL, "
                        + "adminLevel TEXT NOT NULL, "
                        + "FOREIGN KEY (userId) REFERENCES users(id) ON DELETE CASCADE"
                        + ");";
                statement.execute(administratorTable);

                System.out.println("Tables created successfully.");
            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }
        } else {
            System.out.println("Failed to connect to the database.");
        }
    }

    public ResultSet readRecords(Connection conn, String sqlStatement) {
        ResultSet resultSet = null;
        try {
            PreparedStatement statement = conn.prepareStatement(sqlStatement);
            resultSet = statement.executeQuery();
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        }
        return resultSet;
    }

    public static <T> void insertRecords(Connection conn, T object) {

        String sqlStatement;

        try {
            if (object instanceof User) {
                User user = (User) object;
                sqlStatement = "INSERT INTO users (firstName, lastName, username, password, email, phone, address, sex, dob, permissions) "
                        + "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
                try (PreparedStatement statement = conn.prepareStatement(sqlStatement,
                        PreparedStatement.RETURN_GENERATED_KEYS)) {
                    statement.setString(1, user.getFirstName());
                    statement.setString(2, user.getLastName());
                    statement.setString(3, user.getUsername());
                    statement.setString(4, user.getPassword());
                    statement.setString(5, user.getEmail());
                    statement.setString(6, user.getPhone());
                    statement.setString(7, user.getAddress());
                    statement.setString(8, user.getSex());
                    statement.setString(9, user.getDob());
                    statement.setString(10, user.getPermissions().toString()); // Convert Permissions to String
                    statement.executeUpdate();

                    try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                        if (generatedKeys.next()) {
                            long userId = generatedKeys.getLong(1);
                            user.setId(userId); // Set the generated ID

                            if (object instanceof Employee) {
                                Employee employee = (Employee) object;
                                insertEmployee(conn, employee, userId);
                            } else if (object instanceof Administrator) {
                                Administrator administrator = (Administrator) object;
                                insertAdministrator(conn, administrator, userId);
                            }
                        }
                    }
                }
            }
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        }
    }

    private static void insertEmployee(Connection conn, Employee employee, long userId) throws SQLException {
        String sqlStatement = "INSERT INTO employees (userId, socialSecurityNumber, position, payrate, paybasis, baseEarnings) "
                + "VALUES (?, ?, ?, ?, ?, ?)";
        try (PreparedStatement statement = conn.prepareStatement(sqlStatement)) {
            statement.setLong(1, userId);
            statement.setString(2, employee.getSocialSecurityNumber());
            statement.setString(3, employee.getPosition());
            statement.setDouble(4, employee.getPayrate());
            statement.setString(5, employee.getPaybasis().toString());
            statement.setDouble(6, employee.getBaseEarnings());
            statement.executeUpdate();
        }
    }

    private static void insertAdministrator(Connection conn, Administrator administrator, long userId)
            throws SQLException {
        String sqlStatement = "INSERT INTO administrators (userId, adminLevel) VALUES (?, ?)";
        try (PreparedStatement statement = conn.prepareStatement(sqlStatement)) {
            statement.setLong(1, userId);
            statement.setString(2, administrator.getAdminLevel());
            statement.executeUpdate();
        }
    }

    public static void deleteRecords(Connection conn, String sqlStatement) {
        try (PreparedStatement statement = conn.prepareStatement(sqlStatement)) {
            statement.executeUpdate();
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        }
    }
}
