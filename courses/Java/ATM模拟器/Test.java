package atm;

import javax.swing.*;
import java.io.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import atm.MyExceptions.*;

public class Test {
    protected static List<Account> usersList = null;
    protected static Account currentAccount = null;
    protected static Menu menu = null;
    private static File file = new File("users.txt");
    private static Writer fw = null;
    private static Reader fr = null;

    public static void main(String[] args) throws Exception {
        if (!file.exists()) {
            initUsersList();
        }
        usersList = new ArrayList<Account>();
        loadUsersList();
        printUsers();
        menu = new Menu();
    }

    private static void initUsersList() {
        try {
            file.createNewFile();
            fw = new FileWriter(file);
            fw.write("123456 123456 10000\r\n");
            fw.flush();
            fw.close();
        } catch (Exception e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(null, "用户库创建失败");
        }
    }

    public static void loadUsersList() {
        try {
            System.out.println("开始用户读取");
            fr = new FileReader(file);
            BufferedReader bfr = new BufferedReader(fr);
            String line = "";
            while ((line = bfr.readLine()) != null) {
                String[] parameter = line.split("\\s+");
                Account account = new Account(parameter[0], parameter[1], parameter[2]);
                usersList.add(account);
            }
            bfr.close();
            fr.close();
            System.out.println("完成用户读取");
        } catch (Exception e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(null, "用户库读取失败");
        }
    }

    public static void printUsers() {
        System.out.println("已有用户列表：");
        Iterator<Account> iterator = usersList.iterator();
        while (iterator.hasNext()) {
            System.out.println("读取到用户" + iterator.next().getCardID());
        }
    }

    public static void updateUsersList() {
        try {
            fw = new FileWriter(file);
            StringBuilder parameter = new StringBuilder();
            for (Account account : usersList) {
                parameter.append(account.getAllInfo() + "\r\n");
            }
            fw.write(parameter.toString());
            fw.flush();
            fw.close();
        } catch (Exception e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(null, "用户库更新失败");
        }
    }

    public static void exitCurrentAccount() throws Exception {
        if (currentAccount != null) {
            currentAccount = null;
            throw new NoException("退出账户成功");
        } else {
            throw new CardIDException("还没有登录任何账户");
        }
    }
}
