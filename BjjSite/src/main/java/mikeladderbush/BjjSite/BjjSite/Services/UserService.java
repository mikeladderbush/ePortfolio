package mikeladderbush.BjjSite.BjjSite.Services;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import mikeladderbush.BjjSite.BjjSite.Classes.User;
import mikeladderbush.BjjSite.BjjSite.Database.DatabaseStatement;
import mikeladderbush.BjjSite.BjjSite.Repositories.UserRepository;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;
import java.util.Optional;

@Service
public class UserService {

    @Autowired
    private UserRepository userRepository;

    @Autowired
    private DatabaseStatement databaseStatement;

    private final Connection connection;

    @Autowired
    public UserService(Connection connection) {
        this.connection = connection;
    }

    public User addUser(User user) throws SQLException {
        DatabaseStatement.insertRecords(connection, user);
        return user;
    }

    public Optional<User> updatePassword(Long id, String password) {
        Optional<User> userOptional = userRepository.findById(id);
        if (userOptional.isPresent()) {
            User user = userOptional.get();
            user.setPassword(password);
            userRepository.save(user);
            return Optional.of(user);
        }
        return Optional.empty();
    }

    public Optional<User> updateEmail(Long id, String email) {
        Optional<User> userOptional = userRepository.findById(id);
        if (userOptional.isPresent()) {
            User user = userOptional.get();
            user.setEmail(email);
            userRepository.save(user);
            return Optional.of(user);
        }
        return Optional.empty();
    }

    public void deleteUser(Long id) {
        userRepository.deleteById(id);
    }

    public List<User> getAllUsers() {
        return userRepository.findAll();
    }

    public Optional<User> findUserById(Long id) {
        return userRepository.findById(id);
    }
}
