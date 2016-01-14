/**
 * Created by ChrisSnowden on 14/01/2016.
 */
public class NumberExpression extends Expression {

    int value;

    public NumberExpression(int value) {

        this.value = value;

    }

    @Override
    public int value() {
        return value;
    }

    @Override
    public int precedence() {
        return value >= 0 ? 10000: 10;
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }
}
