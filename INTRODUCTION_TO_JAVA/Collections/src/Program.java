import java.util.*;

/**
 * Created by ChrisSnowden on 14/01/2016.
 */
public class Program {


    public static void main(String[] args) {

        testComparePersons();

        List<Person> list = new ArrayList<>();

        getPeople(list);

        System.out.println(list);
        Collections.sort(list);
        System.out.println(list);
        Collections.sort(list, Person.givenNameComparator());
        System.out.println(list);

    }

    private static void testComparePersons() {
        Person ann = new Person("Ann", "Arvark", 22);
        Person ann2 = new Person("Ann", "Arvark", 22);
        Person bob = new Person("Bob", "Arvark", 25);

        if (ann.compareTo(bob) < 0) {
            System.out.println(ann);
            System.out.println(bob);
        } else {
            System.out.println(bob);
            System.out.println(ann);
        }

        if (ann.compareTo(ann2) == 0)
            System.out.println("ann and ann2 are the same");
        if (ann.equals(ann2))
            System.out.println("ann and ann2 are the same");
    }

    private static void getPeople(List<Person> list) {

        Scanner scanner = new Scanner(System.in);
        Person p = null;
        while (true) {

            p = getPerson(scanner);
            if (p == null) break;
            list.add(p);
        }
    }

    private static Person getPerson(Scanner scanner) {

    String fullName = null, givenName = null, surname = null;
    int lastSpace;
    Person person = null;

        System.out.println("Enter a name:");
        if(scanner.hasNext()) {
            fullName = scanner.nextLine().trim();
        }
        lastSpace = fullName.lastIndexOf(' ');
        if(lastSpace > 0) {
            givenName = fullName.substring(0, lastSpace);
            surname = fullName.substring(lastSpace + 1);
            person = new Person(givenName, surname, getAge(scanner,fullName));
        }

    return person;

    }

    private static int getAge(Scanner scanner, String fullName) {

        int age = 0;
        boolean gotAge = false;
        while (!gotAge) {

            System.out.println("How old is " + fullName + "?");

            if(scanner.hasNextInt()) {
                age = scanner.nextInt();
                gotAge = age > 0;
                if(!gotAge)
                    System.out.println("That's negative!");
            } else {
                System.out.println("That's not an integer!");
            }
            scanner.nextLine(); // discard next token, which isn't a valid int
        }
        return age;
    }


}
