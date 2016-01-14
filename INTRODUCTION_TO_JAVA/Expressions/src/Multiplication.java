/**
 * Created by ChrisSnowden on 14/01/2016.
 */
public class Multiplication extends  LBinaryExpression {

    public Multiplication(Expression l, Expression r) {
        super(l, r);
    }

    @Override
    protected int calculate(int v1, int v2) {
        return v1 * v2;
    }

    @Override
    public char symbol() {
        return '*';
    }

    @Override
    public int precedence() {
        return 20;
    }
}
