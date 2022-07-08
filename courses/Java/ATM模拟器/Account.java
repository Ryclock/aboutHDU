package atm;

import java.util.Arrays;

import atm.MyExceptions.*;

public class Account {
    private String cardID;
    private String password;
    private double balance;

    public Account(String cardID, String password, String balance) {
        this.cardID = cardID;
        this.password = password;
        this.balance = Double.parseDouble(balance);
    }

    public String getCardID() {
        return cardID;
    }

    protected String getPassword() {
        return password;
    }

    protected void setPassword(String password) {
        this.password = password;
    }

    public double getBalance() {
        return balance;
    }

    protected void setBalance(double balance) {
        this.balance = balance;
    }

    protected String getAllInfo() {
        return this.cardID + " " + this.password + " " + this.balance;
    }

    protected void TryLogin(String cardID, String password) throws Exception {
        if (!this.cardID.equals(cardID)) {
            throw new CardIDException("该用户不存在");
        } else if (!this.password.equals(password)) {
            throw new PasswordException("密码错误");
        } else {
            throw new NoException("登录成功");
        }
    }

    protected void Withdraw(double amount) throws Exception {
        if (amount < 0) {
            throw new AmountException("无效的取款金额\n取款金额不可为负数");
        }
        if (amount < 100) {
            throw new AmountException("无效的取款金额\n单次取款金额不可少于100");
        }
        if (amount % 100 != 0) {
            throw new AmountException("无效的取款金额\n取款金额应为100的倍数");
        }
        if (amount > 5000) {
            throw new AmountException("无效的取款金额\n单次取款金额不可多于5000");
        }
        if (balance <= amount) {
            throw new AmountException("无效的取款金额\n账户余额不足");
        }
        balance -= amount;
        throw new NoException("取款成功\n此次取出金额：" + amount);
    }

    protected void Deposit(double amount) throws Exception {
        if (amount >= 0) {
            balance += amount;
            throw new NoException("存入成功\n此次存入金额：" + amount);
        } else {
            throw new AmountException("无效的存款金额\n存入金额不能为负数");
        }
    }

    protected void ChangePassword(String newPassword) throws Exception {
        if (newPassword.length() < 6) {
            throw new PasswordException("修改失败，请使用更复杂的密码\n提示：密码不能少于6位");
        }
        if (newPassword.length() == 6) {
            char[] verify = newPassword.toCharArray();
            Arrays.sort(verify);
            if (verify[0] == verify[verify.length - 1]) {
                throw new PasswordException("修改失败，请使用更复杂的密码\n提示：不允许使用6位完全相同的密码");
            }
        }
        this.password = newPassword;
        throw new NoException("修改密码成功");
    }
}