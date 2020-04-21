package complexNumbers.game;

class Warrior extends Character {

    Warrior(String name, int attackPower, int hp) {
        super(name, attackPower, hp);
    }

    public String toString() {
        return "Warrior name: " + getName() + ", attack power: " + getAttackPower() + ", hit points: " + getHp();
    }

    public void attack() {
        System.out.println("Warrior is attacking! Dealt " + getAttackPower() + " damage");
    }

    @Override
    void talk() {
        System.out.println("I am a Warrior!!");
    }

    @Override
    void run() {
        System.out.println("Warrior running");
    }
}

class Paladin extends Character {

    Paladin(String name, int attackPower, int hp) {
        super(name, attackPower, hp);
    }

    public void attack() {
        System.out.println("Paladin is attacking! Dealt " + getAttackPower() + " damage");
    }

    public String toString() {
        return "Paladin name: " + getName() + ", attack power: " + getAttackPower() + ", hit points: " + getHp();
    }

    @Override
    void talk() {
        System.out.println("I am a Paladin!!");
    }

    @Override
    void run() {
        System.out.println("Paladin running");
    }
}

public class Game {
    public static void main(String[] args) {
        Character paladin = makeCharacter(new Paladin("Paladyn Krzysiek", 100, 100));
        Character warrior = makeCharacter(new Warrior("Wojownik Bartek", 150, 80));

        System.out.println(paladin.toString());
        paladin.run();
        paladin.talk();
        paladin.attack();

        System.out.println(warrior.toString());
        warrior.run();
        warrior.talk();
        warrior.attack();
    }

    private static Character makeCharacter(Character x){
        return x;
    }
}
