package mikeladderbush.BjjSite.BjjSite.Factories;

import java.util.function.Consumer;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import mikeladderbush.BjjSite.BjjSite.Classes.Administrator;
import mikeladderbush.BjjSite.BjjSite.Classes.Employee;
import mikeladderbush.BjjSite.BjjSite.Classes.User;
import mikeladderbush.BjjSite.BjjSite.Enums.Permissions;
import mikeladderbush.BjjSite.BjjSite.Services.UserService;

@Component
public class UserFactory {

    private final UserService userService;

    @Autowired
    public UserFactory(UserService userService) {
        this.userService = userService;
    }

    // Method to create a User with default values
    public User createUser() {
        Permissions permissions = Permissions.USER_ACCESS;
        return new User.UserBuilder<>(permissions).buildUser();
    }

    public User createUser(Consumer<User.UserBuilder<?>> consumer) {
        Permissions permissions = Permissions.USER_ACCESS;
        User.UserBuilder<?> builder = new User.UserBuilder<>(permissions);
        consumer.accept(builder);
        return builder.buildUser();
    }

    public Employee createEmployee() {
        Permissions permissions = Permissions.FULL_CONTROL;
        return new Employee.EmployeeBuilder<>(permissions).buildUser();
    }

    public Employee createEmployee(Consumer<Employee.EmployeeBuilder<?>> consumer) {
        Permissions permissions = Permissions.EMPLOYEE_ACCESS;
        Employee.EmployeeBuilder<?> builder = new Employee.EmployeeBuilder<>(permissions);
        consumer.accept(builder);
        return builder.buildUser();
    }

    public Administrator createAdministrator() {
        Permissions permissions = Permissions.FULL_CONTROL;
        return new Administrator.AdministratorBuilder(permissions).buildUser();
    }

    public Administrator createAdministrator(Consumer<Administrator.AdministratorBuilder> consumer) {
        Permissions permissions = Permissions.FULL_CONTROL;
        Administrator.AdministratorBuilder builder = new Administrator.AdministratorBuilder(permissions);
        consumer.accept(builder);
        return builder.buildUser();
    }
}
