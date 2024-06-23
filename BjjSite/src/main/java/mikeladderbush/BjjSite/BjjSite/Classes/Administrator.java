package mikeladderbush.BjjSite.BjjSite.Classes;

import mikeladderbush.BjjSite.BjjSite.Enums.Permissions;

/**
 * Represents an Admin.
 */
public class Administrator extends Employee {

    private final String adminLevel;

    private Administrator(AdministratorBuilder builder) {
        super(builder);
        this.adminLevel = builder.adminLevel;
    }

    public static class AdministratorBuilder extends EmployeeBuilder<AdministratorBuilder> {

        private String adminLevel = "DEFAULT ADMIN";

        public AdministratorBuilder(Permissions permissions) {
            super(permissions);
        }

        public AdministratorBuilder adminLevel(String value) {
            this.adminLevel = value;
            return self();
        }

        @Override
        protected AdministratorBuilder self() {
            return this;
        }

        @Override
        public Administrator buildUser() {
            return new Administrator(this);
        }
    }

    public Long getId() {
        return id;
    }

    public String getAdminLevel() {
        return adminLevel;
    }
}
