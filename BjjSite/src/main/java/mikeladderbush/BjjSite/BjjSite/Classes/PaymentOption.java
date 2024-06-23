package mikeladderbush.BjjSite.BjjSite.Classes;


public class PaymentOption {

    private String id;
    private String name;
    private String cardNumber;
    private String expirationDate;
    private String confirmationCode;
    private String cardType;
    private String billingAddress;
    private String billingZipCode;

    public static class PaymentOptionBuilder {

        private String id;
        private String name = "NO_PAYMENT_NAME_ON_FILE";
        private String cardNumber = "NO_CARD_NUMBER_ON_FILE";
        private String expirationDate = "NO_EXPIRATION_DATE_ON_FILE";
        private String confirmationCode = "NO_CONFIRMATION_CODE_ON_FILE";
        private String cardType = "NO_CARD_TYPE_ON_FILE";
        private String billingAddress = "NO_BILLING_ADDRESS_ON_FILE";
        private String billingZipCode = "NO_BILLING_ZIP_CODE_ON_FILE";

        public PaymentOptionBuilder(String id) {
            this.id = id;
        }

        public PaymentOptionBuilder name(String value) {
            this.name = value;
            return this;
        }

        public PaymentOptionBuilder cardNumber(String value) {
            this.cardNumber = value;
            return this;
        }

        public PaymentOptionBuilder expirationDate(String value) {
            this.expirationDate = value;
            return this;
        }

        public PaymentOptionBuilder confirmationCode(String value) {
            this.confirmationCode = value;
            return this;
        }

        public PaymentOptionBuilder cardType(String value) {
            this.cardType = value;
            return this;
        }

        public PaymentOptionBuilder billingAddress(String value) {
            this.billingAddress = value;
            return this;
        }

        public PaymentOptionBuilder billingZipCode(String value) {
            this.billingZipCode = value;
            return this;
        }

        public PaymentOption buildPaymentOption() {
            return new PaymentOption(this);
        }

    }

    private PaymentOption(PaymentOptionBuilder paymentOptionBuilder) {
        id = paymentOptionBuilder.id;
        name = paymentOptionBuilder.name;
        cardNumber = paymentOptionBuilder.cardNumber;
        expirationDate = paymentOptionBuilder.expirationDate;
        confirmationCode = paymentOptionBuilder.confirmationCode;
        cardType = paymentOptionBuilder.cardType;
        billingAddress = paymentOptionBuilder.billingAddress;
        billingZipCode = paymentOptionBuilder.billingZipCode;
    }

    /**
     * Retrieves the ID of the contact.
     * 
     * @return The ID of the contact.
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

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setCardNumber(String cardNumber) {
        this.cardNumber = cardNumber;
    }

    public String getCardNumber() {
        return cardNumber;
    }

    public void setExpirationDate(String expirationDate) {
        this.expirationDate = expirationDate;
    }

    public String getExpirationDate() {
        return expirationDate;
    }

    public void setConfirmationCode(String confirmationCode) {
        this.confirmationCode = confirmationCode;
    }

    public String getConfirmationCode() {
        return confirmationCode;
    }

    public void setCardType(String cardType) {
        this.cardType = cardType;
    }

    public String getCardType() {
        return cardType;
    }

    public void setBillingAddress(String billingAddress) {
        this.billingAddress = billingAddress;
    }

    public String getBillingAddress() {
        return billingAddress;
    }

    public void setBillingZipCode(String billingZipCode) {
        this.billingZipCode = billingZipCode;
    }

    public String getBillingZipCode() {
        return billingZipCode;
    }

}
