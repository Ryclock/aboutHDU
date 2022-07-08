package atm;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import atm.MyExceptions.*;

public class LoginGui extends JFrame implements ActionListener {
    private JLabel pleaseInput, cardIDJLabel, passwordJLabel;
    private JTextField cardID;
    private JPasswordField password;
    private JButton cancel, tryLogin, reset;

    public LoginGui() throws Exception {
        super("登录界面");
        this.setBounds(500, 500, 350, 270);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.setLayout(null);

        if (Test.currentAccount != null) {
            throw new CardIDException("请退出当前用户再进行此操作");
        } else {
            Test.menu.hideScreen();
        }

        pleaseInput = new JLabel("请输入");
        pleaseInput.setSize(70, 30);
        pleaseInput.setLocation(140, 10);
        pleaseInput.setFont(new Font("宋体", Font.BOLD, 18));
        this.add(pleaseInput);

        cardIDJLabel = new JLabel("卡号:");
        cardIDJLabel.setSize(50, 30);
        cardIDJLabel.setLocation(80, 60);
        cardIDJLabel.setFont(new Font("宋体", Font.BOLD, 16));
        this.add(cardIDJLabel);

        cardID = new JTextField(20);
        cardID.setSize(120, 30);
        cardID.setLocation(130, 60);
        this.add(cardID);

        passwordJLabel = new JLabel("密码:");
        passwordJLabel.setSize(50, 30);
        passwordJLabel.setLocation(80, 100);
        passwordJLabel.setFont(new Font("宋体", Font.BOLD, 16));
        this.add(passwordJLabel);

        password = new JPasswordField(20);
        password.setSize(120, 30);
        password.setLocation(130, 100);
        this.add(password);

        cancel = new JButton("返回");
        cancel.setSize(80, 40);
        cancel.setLocation(30, 160);
        cancel.addActionListener(this);
        this.add(cancel);

        tryLogin = new JButton("登录");
        tryLogin.setSize(80, 40);
        tryLogin.setLocation(130, 160);
        tryLogin.addActionListener(this);
        this.add(tryLogin);

        reset = new JButton("重置");
        reset.setSize(80, 40);
        reset.setLocation(230, 160);
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
            cardID.setText("");
            password.setText("");
        }
        if (e.getActionCommand().equals("登录")) {
            for (int i = 0; i < Test.usersList.size(); i++) {
                try {
                    Test.usersList.get(i).TryLogin(cardID.getText(), String.valueOf(password.getPassword()));
                } catch (NoException e0) {
                    this.setVisible(false);
                    JOptionPane.showMessageDialog(this, e0.getMessage());
                    Test.currentAccount = Test.usersList.get(i);
                    Test.menu.showScreen();
                    break;
                } catch (CardIDException e1) {
                    if (i == Test.usersList.size() - 1) {
                        JOptionPane.showMessageDialog(this, e1.getMessage());
                    }
                } catch (PasswordException e1) {
                    JOptionPane.showMessageDialog(this, e1.getMessage());
                    break;
                } catch (Exception e1) {
                    e1.printStackTrace();
                    break;
                }
            }
        }
    }
}
