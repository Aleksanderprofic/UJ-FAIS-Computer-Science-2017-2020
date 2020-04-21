package complexNumbers.game;

public abstract class Character implements Attack {

    Character(String name, int attackPower, int hp) {
        this.name = name;
        this.attackPower = attackPower;
        this.hp = hp;
    }
    private int attackPower;
    private String name;
    private int hp;

    public int getAttackPower() {
        return attackPower;
    }

    public String getName() {
        return name;
    }

    public int getHp() {
        return hp;
    }

    abstract void talk();
    abstract void run();
}
