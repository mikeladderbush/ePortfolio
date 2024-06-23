package mikeladderbush.BjjSite.BjjSite.Repositories;

import mikeladderbush.BjjSite.BjjSite.Classes.User;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface UserRepository extends JpaRepository<User, Long> {

}
