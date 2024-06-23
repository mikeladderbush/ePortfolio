package mikeladderbush.BjjSite.BjjSite.Classes;

import java.util.List;

import jakarta.persistence.ElementCollection;
import jakarta.persistence.Entity;
import jakarta.persistence.Enumerated;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import mikeladderbush.BjjSite.BjjSite.Enums.Permissions;
import mikeladderbush.BjjSite.BjjSite.Interfaces.UserUtils;

/**
 * Represents a User.
 */
@Entity
@Table(name = "users")
public class User implements UserUtils {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    protected Long id;

    private String firstName;
    private String lastName;
    protected String username;
    protected String password;
    protected String email;
    private String phone;
    private String address;
    private String sex;
    private String dob;

    @ElementCollection
    private List<PaymentOption> paymentOptions;

    @Enumerated
    protected Permissions permissions;

    protected User(UserBuilder<?> UserBuilder) {
        firstName = UserBuilder.firstName;
        lastName = UserBuilder.lastName;
        phone = UserBuilder.phone;
        username = UserBuilder.username;
        password = UserBuilder.password;
        email = UserBuilder.email;
        address = UserBuilder.address;
        sex = UserBuilder.sex;
        dob = UserBuilder.dob;
        paymentOptions = UserBuilder.paymentOptions;
        permissions = UserBuilder.permissions;
    }

    public static class UserBuilder<T extends UserBuilder<T>> {

        private String firstName = "NO FIRST NAME ON FILE";
        private String lastName = "NO LAST NAME ON FILE";
        private String phone = "NO EMAIL ON FILE";
        private String username = "NO FIRST NAME ON FILE";
        protected String password = "NO LAST NAME ON FILE";
        protected String email = "NO PHONE NUMBER ON FILE";
        private String address = "NO ADDRESS ON FILE";
        private String sex = "DEFAULT";
        private String dob = "DEFAULT";
        private List<PaymentOption> paymentOptions = null;
        private final Permissions permissions;

        public UserBuilder(Permissions permissions) {
            this.permissions = permissions;
        }

        public T firstName(String value) {
            this.firstName = value;
            return self();
        }

        public T lastName(String value) {
            this.lastName = value;
            return self();
        }

        public T phone(String value) {
            this.phone = value;
            return self();
        }

        public T username(String value) {
            this.username = value;
            return self();
        }

        public T password(String value) {
            this.password = value;
            return self();
        }

        public T email(String value) {
            this.email = value;
            return self();
        }

        public T address(String value) {
            this.address = value;
            return self();
        }

        public T sex(String value) {
            this.sex = value;
            return self();
        }

        public T dob(String value) {
            this.dob = value;
            return self();
        }

        public T paymentOptions(List<PaymentOption> value) {
            this.paymentOptions = value;
            return self();
        }

        protected T self() {
            return (T) this;
        }

        public User buildUser() {
            return new User(this);
        }
    }

    /**
     * Retrieves the ID of the User.
     * 
     * @return The ID of the User.
     */
    public Long getId() {
        return id;
    }

    /**
     * For testing purpose only.
     * 
     * @param id
     */
    public void setId(Long id) {
        this.id = id;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        if (firstName != null) {
            this.firstName = firstName;
        } else {
            throw new IllegalArgumentException("First Name cannot be null");
        }
    }

    public String getLastName() {
        return firstName;
    }

    public void setLastName(String lastName) {
        if (lastName != null) {
            this.lastName = lastName;
        } else {
            throw new IllegalArgumentException("Last Name cannot be null");
        }
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        if (phone != null) {
            this.phone = phone;
        } else {
            throw new IllegalArgumentException("A Phone number is necessary");
        }
    }

    /**
     * Retrieves the username of the User.
     * 
     * @return The username of the User.
     */
    public String getUsername() {
        return username;
    }

    /**
     * Sets the username of the User.
     * 
     * @param username The username of the User.
     * @throws IllegalArgumentException if the username is null or exceeds 10
     *                                  characters.
     */
    public void setUsername(String username) {
        if (username != null && username.length() <= 10) {
            this.username = username;
        } else {
            throw new IllegalArgumentException("Username must be fewer than 10 characters");
        }
    }

    /**
     * Retrieves the password of the User.
     * 
     * @return The password of the User.
     */
    public String getPassword() {
        return password;
    }

    /**
     * Sets the password of the User.
     * 
     * @param Password The password of the User.
     * @throws IllegalArgumentException if the password is null or exceeds 10
     *                                  characters.
     */
    public void setPassword(String password) {
        if (password != null && password.length() <= 10) {
            this.password = password;
        } else {
            throw new IllegalArgumentException("Password must be fewer than 10 characters");
        }
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        if (email != null) {
            this.email = email;
            // ADD EMAIL ERROR CHECKING
        } else {
            throw new IllegalArgumentException("Email error");
        }
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }

    public String getDob() {
        return dob;
    }

    public void setDob(String dob) {
        this.dob = dob;
    }

    public List<PaymentOption> getPaymentOptions() {
        return paymentOptions;
    }

    public void setPaymentOptions(List<PaymentOption> paymentOptions) {
        this.paymentOptions = paymentOptions;
    }

    public Permissions getPermissions() {
        return permissions;
    }

    public void setPermissions(Permissions permissions) {
        if (permissions != null) {
            this.permissions = permissions;
        } else {
            throw new IllegalArgumentException("Permission error");
        }
    }
}
