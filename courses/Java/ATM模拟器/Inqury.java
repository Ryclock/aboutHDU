package atm;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import atm.MyExceptions.*;

public class Inqury extends JFrame implements ActionListener {
    private JLabel inquryJLabel, cardIDJLabel, amountJLabel;
    private JTextField cardID, amount;
    private JButton returnToMenu;

    public Inqury() throws Exception {
        super("查询界面");
        this.setBounds(500, 500, 300, 250);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.setLayout(null);

        if (Test.currentAccount == null) {
            throw new CardIDException("还没有登录任何账户");
        } else {
            Test.menu.hideScreen();
        }

        inquryJLabel = new JLabel("查询成功");
        inquryJLabel.setSize(100, 30);
        inquryJLabel.setLocation(100, 10);
        inquryJLabel.setFont(new Font("宋体", Font.BOLD, 18));
        this.add(inquryJLabel);

        cardIDJLabel = new JLabel("账户信息:");
        cardIDJLabel.setSize(80, 30);
        cardIDJLabel.setLocation(50, 50);
        cardIDJLabel.setFont(new Font("宋体", Font.BOLD, 16));
        this.add(cardIDJLabel);

        cardID = new JTextField(20);
        cardID.setSize(90, 30);
        cardID.setLocation(130, 50);
        cardID.setText(Test.currentAccount.getCardID());
        cardID.setEditable(false);
        this.add(cardID);

        amountJLabel = new JLabel("现有金额:");
        amountJLabel.setSize(80, 30);
        amountJLabel.setLocation(50, 90);
        amountJLabel.setFont(new Font("宋体", Font.BOLD, 16));
        this.add(amountJLabel);

        amount = new JTextField(20);
        amount.setSize(90, 30);
        amount.setLocation(130, 90);
        amount.setText(String.valueOf(Test.currentAccount.getBalance()));
        amount.setEditable(false);
        this.add(amount);

        returnToMenu = new JButton("返回");
        returnToMenu.setSize(80, 40);
        returnToMenu.setLocation(180, 150);
        returnToMenu.addActionListener(this);
        this.add(returnToMenu);

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("返回")) {
            this.setVisible(false);
            Test.menu.showScreen();
        }
    }
}
