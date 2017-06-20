import React, { Component } from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  Button,
  TextInput,
  Linking
} from 'react-native';


export default class SVMXExternalApp extends Component {
  constructor(props) {
    super(props);
    this.state = {text: ''};
  }

  componentDidMount() {
    Linking.addEventListener('url', this._handleOpenURL);
  }

  _handleOpenURL(event) {
    console.log(event.url);
  }

  handleBtnClick = () => {
    console.log('this is:', this);
    let data = this.state.text;
    this.launchedSVMXApp(data);
  }

  launchedSVMXApp(data) {

    let servicemaxSchemaName = 'svmx';
    let url = servicemaxSchemaName + '://' + encodeURIComponent(data);

    Linking.canOpenURL(url).then(supported => {
      console.log('URL: ' + url + '; + supported? ' + supported);
      /*
      if (!supported) {
        console.log('Can\'t handle url: ' + url);
      } else {
        return Linking.openURL(url);
      }
      */
      return Linking.openURL(url);
    }).catch(err => console.error('An error occurred', err));
  }

  render() {
    return(
      <View style={styles.container}>
        <Text style = {styles.welcome}>
          Welcome
        </Text>

         <TextInput
           multiline = {true}
           editable = {true}
           numberOfLines = {4}
           placeholder =  {'Please enter json data...'}
           onChangeText={(text) => this.setState({text})}
           value={this.state.text}
         />

         <Button
           onPress= {this.handleBtnClick}
           title="Launch ServiceMax"
         />
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  }
});

AppRegistry.registerComponent('SVMXExternalApp', () => SVMXExternalApp);
