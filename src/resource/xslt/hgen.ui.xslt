<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
                  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                  xmlns:fo="http://www.w3.org/1999/XSL/Format">
<xsl:output method="xml" version="1.0" encoding="utf-8" indent="yes"/>

<xsl:param name="breeds" />
<xsl:param name="cultures" />
<xsl:param name="professions" />
<xsl:param name="procontra" />
<xsl:param name="talents" />
<xsl:param name="basehero" />
<xsl:param name="specialabilities" />

<xsl:variable name="breeds_doc" select="document($breeds)" />
<xsl:variable name="cultures_doc" select="document($cultures)" />
<xsl:variable name="professions_doc" select="document($professions)" />
<xsl:variable name="procontra_doc" select="document($procontra)" />
<xsl:variable name="talents_doc" select="document($talents)" />
<xsl:variable name="basehero_doc" select="document($basehero)" />
<xsl:variable name="specialabilities_doc" select="document($specialabilities)" />

<xsl:template match="/">
  <xsl:element name="xsl:stylesheet" >
    <xsl:attribute name="version"><xsl:value-of select="'1.0'" /></xsl:attribute>
    <xsl:attribute namespace="xmlns" name="fo"><xsl:value-of select="'http://www.w3.org/1999/XSL/Format'" /></xsl:attribute>
    <xsl:attribute name="exclude-result-prefixes"><xsl:value-of select="'ns_1'" /></xsl:attribute>

    <xsl:element name="xsl:param" ><xsl:attribute name="name"><xsl:value-of select="'breeds'" /></xsl:attribute></xsl:element>
    <xsl:element name="xsl:param" ><xsl:attribute name="name"><xsl:value-of select="'cultures'" /></xsl:attribute></xsl:element>
    <xsl:element name="xsl:param" ><xsl:attribute name="name"><xsl:value-of select="'talents'" /></xsl:attribute></xsl:element>
    <xsl:element name="xsl:param" ><xsl:attribute name="name"><xsl:value-of select="'basehero'" /></xsl:attribute></xsl:element>

    <xsl:element name="xsl:template" >
      <xsl:attribute name="match"><xsl:value-of select="'/'" /></xsl:attribute>
      <xsl:copy>
          <xsl:apply-templates select="@*|node()"/>
      </xsl:copy>
    </xsl:element>

  </xsl:element>
</xsl:template>

<xsl:template match="@*|node()">
    <xsl:copy>
        <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
</xsl:template>

<xsl:template match="object[@id = 'hero_list_store']">  
    <xsl:copy>
        <xsl:apply-templates select="@*|node()"/>
        <data>
        <xsl:element name="xsl:for-each">
          <xsl:attribute name="select"><xsl:value-of select="'//hero'" /></xsl:attribute>      
            <row>
              <col id="0" translatable="yes">
                <xsl:element name="xsl:value-of">
                  <xsl:attribute name="select"><xsl:value-of select="'@name'" /></xsl:attribute>
                </xsl:element>
              </col>
            </row>
        </xsl:element>
        </data>
    </xsl:copy>
</xsl:template>

<xsl:template match="object[@id = 'hgen_pro_liststore']">  
    <xsl:call-template name="copy_node_and_add_rows">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$procontra_doc//pro" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_contra_liststore']">  
    <xsl:call-template name="copy_node_and_add_rows">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$procontra_doc//contra" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_sa_liststore']">  
    <xsl:call-template name="copy_node_and_add_rows">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$specialabilities_doc//specialability" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_breed']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$breeds_doc//breed" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_culture']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$cultures_doc//culture" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_profession']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$professions_doc//profession" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_talent_fight']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$talents_doc//group[@name = 'Kampf']/talent[@type='special' and not(@usage)]" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_talent_fight_distance']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$talents_doc//group[@name = 'Kampf']/talent[@type='special' and @usage]" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_talent_body']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$talents_doc//group[@name = 'Körper']/talent[@type='special']" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_talent_body']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$talents_doc//group[@name = 'Körper']/talent[@type='special']" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_talent_society']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$talents_doc//group[@name = 'Gesellschaft']/talent[@type='special']" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_talent_nature']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$talents_doc//group[@name = 'Natur']/talent[@type='special']" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_talent_wisdom']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$talents_doc//group[@name = 'Wissen']/talent[@type='special']" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="object[@id = 'hgen_talent_craft']">  
    <xsl:call-template name="copy_node_and_add_items">
      <xsl:with-param name="nodes" select = "@*|node()" />
      <xsl:with-param name="items" select = "$talents_doc//group[@name = 'Handwerk']/talent[@type='special']" />
    </xsl:call-template>
</xsl:template>

<xsl:template name="copy_node_and_add_items">
    <xsl:param name = "nodes" />
    <xsl:param name = "items" />
    <xsl:copy>
        <xsl:copy-of select="$nodes"/>
        <items>
        <xsl:for-each select="$items">   
            <xsl:sort select="@name"/>
            <item translatable="yes"><xsl:value-of select="@name" /></item>            
        </xsl:for-each>
        </items>
    </xsl:copy>
</xsl:template>

<xsl:template name="copy_node_and_add_rows">
    <xsl:param name = "nodes" />
    <xsl:param name = "items" />
    <xsl:copy>
        <xsl:copy-of select="$nodes"/>
        <data>
        <xsl:for-each select="$items">   
            <xsl:sort select="@name"/>
            <row><col id="0" translatable="yes"><xsl:value-of select="@name" /></col></row>         
        </xsl:for-each>
        </data>
    </xsl:copy>
</xsl:template>

</xsl:stylesheet>
