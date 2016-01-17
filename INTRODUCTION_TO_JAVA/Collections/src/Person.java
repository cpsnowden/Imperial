import java.util.Comparator;

/**
 * Created by ChrisSnowden on 14/01/2016.
 */
public class Person implements Comparable<Person> {


    private final String givenNames;
    private final String surname;
    private final int age;

    public Person(String givenNames, String surname, int age) {
        this.givenNames = givenNames;
        this.surname = surname;
        this.age = age;
    }

    public String getGivenNames() {
        return givenNames;
    }

    public String getSurname() {
        return surname;
    }

    public int getAge() {
        return age;
    }

    @Override
    public String toString() {
        return givenNames + " " + surname + "(" + age + ")";
    }

    @Override
    public int compareTo(Person person) {
        int sN = this.surname.compareToIgnoreCase(person.getSurname());
        int gN = this.givenNames.compareToIgnoreCase(person.getGivenNames());

        if(sN != 0)
            return sN;
        else if(gN != 0)
            return gN;
        else
            return this.age - person.getAge();
    }


    public static Comparator<Person> givenNameComparator() {
        return new Comparator<Person>() {
            @Override
            public int compare(Person o1, Person o2) {
                return o1.givenNames.compareTo(o2.givenNames);
            }
        };
    }


    @Override
    public boolean equals(Object obj) {

        if(obj == null)
            return false;

        if(obj instanceof Person) {

            return this.compareTo((Person) obj) == 0;
        }

        return false;
    }
}
