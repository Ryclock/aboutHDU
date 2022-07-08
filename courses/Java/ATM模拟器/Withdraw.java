package atm;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import atm.MyExceptions.*;

public class Withdraw extends JFrame implements ActionListener {
    private JLabel pleaseInput, amountJLabel;
    private JTextField amount;
    private JButton cancel, tryDeposit, reset;

    public Withdraw() throws Exception {
        super("取款界面");
        this.setBounds(500, 500, 320, 250);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.setLayout(null);

        if (Test.currentAccount == null) {
            throw new CardIDException("还没有登录任何账户");
        } else {
            Test.menu.hideScreen();
        }

        pleaseInput = new JLabel("请输入");
        pleaseInput.setSize(70, 30);
        pleaseInput.setLocation(120, 10);
        pleaseInput.setFont(new Font("宋体", Font.BOLD, 18));
        this.add(pleaseInput);

        amountJLabel = new JLabel("金额:");
        amountJLabel.setSize(50, 30);
        amountJLabel.setLocation(50, 60);
        amountJLabel.setFont(new Font("宋体", Font.BOLD, 16));
        this.add(amountJLabel);

        amount = new JTextField(20);
        amount.setSize(120, 30);
        amount.setLocation(100, 60);
        this.add(amount);

        cancel = new JButton("返回");
        cancel.setSize(80, 40);
        cancel.setLocation(10, 140);
        cancel.addActionListener(this);
        this.add(cancel);

        tryDeposit = new JButton("取款");
        tryDeposit.setSize(80, 40);
        tryDeposit.setLocation(110, 140);
        tryDeposit.addActionListener(this);
        this.add(tryDeposit);

        reset = new JButton("重置");
        reset.setSize(80, 40);
        reset.setLocation(210, 140);
        reset.addActionListener(this);
        this.add(reset);

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("返回")) {
            this.setVisible(false);
            Test.menu.showScreen();
        }
        if (e.getActionCommand().equals("重置")) {
            amount.setText("");
        }
        if (e.getActionCommand().equals("取款")) {
            try {
                Test.currentAccount.Withdraw(Double.parseDouble(amount.getText()));
            } catch (NoException e0) {
                amount.setText("");
                JOptionPane.showMessageDialog(this, e0.getMessage());
                this.setVisible(false);
                Test.menu.showScreen();
            } catch (CardIDException e1) {
                JOptionPane.showMessageDialog(this, e1.getMessage());
            } catch (AmountException e1) {
                JOptionPane.showMessageDialog(this, e1.getMessage());
            } catch (Exception e1) {
                e1.printStackTrace();
            }
        }
    }
}