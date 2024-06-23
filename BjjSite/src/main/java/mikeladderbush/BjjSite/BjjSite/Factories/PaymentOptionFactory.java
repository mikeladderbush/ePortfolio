package mikeladderbush.BjjSite.BjjSite.Factories;

import java.util.function.Consumer;

import mikeladderbush.BjjSite.BjjSite.Classes.PaymentOption;
import mikeladderbush.BjjSite.BjjSite.Services.PaymentOptionService;

public class PaymentOptionFactory {

    private static final PaymentOptionService paymentOptionService = new PaymentOptionService();

    // Method to create a PaymentOption with default values
    public static PaymentOption createPaymentOption() {
        String id = paymentOptionService.generateId();
        return new PaymentOption.PaymentOptionBuilder(id).buildPaymentOption();
    }

    public static PaymentOption createPaymentOption(Consumer<PaymentOption.PaymentOptionBuilder> consumer) {
        String id = paymentOptionService.generateId();
        PaymentOption.PaymentOptionBuilder builder = new PaymentOption.PaymentOptionBuilder(id);
        consumer.accept(builder);
        return builder.buildPaymentOption();
    }
}
