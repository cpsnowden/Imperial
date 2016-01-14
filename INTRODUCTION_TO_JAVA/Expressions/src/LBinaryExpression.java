/**
 * Created by ChrisSnowden on 14/01/2016.
 */
public abstract class LBinaryExpression extends Expression{

    Expression l, r;

    protected abstract int calculate(int v1, int v2);

    public LBinaryExpression(Expression l, Expression r) {
        this.l = l;
        this.r = r;
    }

    public Expression left() {
        return l;
    }

    public Expression right() {
        return r;
    }

    public abstract char symbol();

    @Override
    public String toString() {

        String toPrint = "";

        boolean left_lower = l.precedence() < precedence();
        if(left_lower) {
            toPrint += "(";
        }

        toPrint += l.toString();

        if(left_lower) {
            toPrint += ")";
        }

        toPrint += symbol();

        boolean right_lower = r.precedence() <= precedence();

        if(right_lower) {
            toPrint += "(";
        }

        toPrint += r.toString();

        if(right_lower) {
            toPrint += ")";
        }

        return toPrint;

    }

    @Override
    public int value() {
        return calculate(l.value(),r.value());
    }

}
